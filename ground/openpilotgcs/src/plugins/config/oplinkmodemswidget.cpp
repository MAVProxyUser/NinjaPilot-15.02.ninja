/**
 ******************************************************************************
 *
 * @file       oplinkmodemswidget.cpp
 * @brief      Two OPLink modems on USB at once: see, edit, save, pair and
 *             test them with no flight controller.  See oplinkmodemswidget.h.
 *****************************************************************************/
#include "oplinkmodemswidget.h"

#include "uavobjectmanager.h"
#include "uavobjectsinit.h"
#include "uavobject.h"
#include "uavobjectfield.h"
#include "uavtalk/uavtalk.h"
#include "uavtalk/telemetrymanager.h"
#include "ophid/inc/ophid.h"
#include "ophid/inc/ophid_usbmon.h"
#include "oplinkstatus.h"
#include "oplinksettings.h"
#include "objectpersistence.h"
#include "firmwareiapobj.h"
#include <coreplugin/icore.h>
#include <coreplugin/connectionmanager.h>
#include <extensionsystem/pluginmanager.h>

#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QEventLoop>
#include <QCoreApplication>

static const int POLL_PERIOD_MS        = 1000;
static const int REBOOT_STEP_MS        = 700;
static const int LINKTEST_COUNT        = 20;
static const int LINKTEST_PERIOD_MS    = 200;
static const int LINKTEST_SETTLE_MS    = 1500;
static const quint8 OPLINK_BOARD_TYPE  = 0x03;
static const quint16 IAP_STEP_1        = 1122;
static const quint16 IAP_STEP_2        = 2233;
static const quint16 IAP_STEP_3_REBOOT = 4455; // reset straight back into the firmware

/* ------------------------------------------------------------------ session */

OPLinkModemSession::OPLinkModemSession(UAVObjectManager *mainManager, const QString &serial, const QString &product, QObject *parent) :
    QObject(parent), m_private(false), m_open(false), m_serial(serial), m_product(product),
    m_hid(NULL), m_manager(mainManager), m_talk(NULL), m_rebootStage(-1), m_settingsPolls(0)
{
    bindObjects(mainManager);
    m_pollTimer   = new QTimer(this);
    m_rebootTimer = new QTimer(this);
    connect(m_pollTimer, SIGNAL(timeout()), this, SLOT(poll()));
    connect(m_rebootTimer, SIGNAL(timeout()), this, SLOT(rebootStep()));
}

OPLinkModemSession::OPLinkModemSession(const QString &serial, const QString &product, QObject *parent) :
    QObject(parent), m_private(true), m_open(false), m_serial(serial), m_product(product),
    m_hid(NULL), m_manager(NULL), m_talk(NULL), m_rebootStage(-1), m_settingsPolls(0)
{
    m_pollTimer   = new QTimer(this);
    m_rebootTimer = new QTimer(this);
    connect(m_pollTimer, SIGNAL(timeout()), this, SLOT(poll()));
    connect(m_rebootTimer, SIGNAL(timeout()), this, SLOT(rebootStep()));
}

OPLinkModemSession::~OPLinkModemSession()
{
    close();
    if (m_private && m_manager) {
        delete m_manager;
    }
}

void OPLinkModemSession::bindObjects(UAVObjectManager *manager)
{
    m_status      = OPLinkStatus::GetInstance(manager);
    m_settings    = OPLinkSettings::GetInstance(manager);
    m_persistence = ObjectPersistence::GetInstance(manager);
    m_iap = FirmwareIAPObj::GetInstance(manager);
}

bool OPLinkModemSession::open()
{
    if (m_open) {
        return true;
    }
    if (m_private) {
        if (!m_manager) {
            m_manager = new UAVObjectManager();
            UAVObjectsInitialize(m_manager);
            bindObjects(m_manager);
        }
        // RawHID's constructor blocks its caller until its read thread has opened
        // the device, and the bundled hidapi repopulates its device list from the
        // GUI thread's run loop: opening from the GUI thread starves that and the
        // enumeration comes back empty.  Build it on a worker thread and keep the
        // GUI loop running meanwhile.
        RawHID *hid = NULL;
        QEventLoop wait;
        QThread *worker = QThread::create([&hid, this]() {
            hid = new RawHID(m_serial);
            hid->moveToThread(QCoreApplication::instance()->thread());
        });
        connect(worker, SIGNAL(finished()), &wait, SLOT(quit()));
        worker->start();
        wait.exec();
        delete worker;
        m_hid = hid;
        if (!m_hid || !m_hid->open(QIODevice::ReadWrite)) {
            qWarning() << "OPLinkModemSession: could not open" << m_serial;
            delete m_hid;
            m_hid = NULL;
            return false;
        }
        connect(m_hid, SIGNAL(closed()), this, SLOT(onDeviceClosed()));
        m_talk = new UAVTalk(m_hid, m_manager);
        // UAVTalk does not pull from its device by itself; the telemetry manager
        // normally wires this up, here we are the telemetry manager
        connect(m_hid, SIGNAL(readyRead()), m_talk, SLOT(processInputStream()));
    }
    m_open = true;
    m_settingsPolls = 0;
    m_pollTimer->start(POLL_PERIOD_MS);
    poll();
    return true;
}

void OPLinkModemSession::close()
{
    m_pollTimer->stop();
    m_rebootTimer->stop();
    if (m_talk) {
        delete m_talk;
        m_talk = NULL;
    }
    if (m_hid) {
        m_hid->close();
        m_hid->deleteLater();
        m_hid = NULL;
    }
    m_open = false;
}

void OPLinkModemSession::onDeviceClosed()
{
    // the modem went away (unplugged, rebooting): drop the session, the page rescans
    m_pollTimer->stop();
    m_rebootTimer->stop();
    m_open = false;
    emit closed();
}

void OPLinkModemSession::send(UAVObject *obj)
{
    if (!m_open) {
        return;
    }
    if (m_private) {
        m_talk->sendObject(obj, false, false);
    } else {
        obj->updated();
    }
}

void OPLinkModemSession::request(UAVObject *obj)
{
    if (!m_open) {
        return;
    }
    if (m_private) {
        m_talk->sendObjectRequest(obj, false);
    } else {
        obj->requestUpdate();
    }
}

void OPLinkModemSession::poll()
{
    // the modem streams OPLinkStatus by itself; settings only on request, and
    // a few times, so an edit in progress is not overwritten every second
    if (m_private) {
        request(m_status);
    }
    // settings every 5 s (the form keeps the user's edits, only the role line follows)
    if ((m_settingsPolls++ % 5) == 0) {
        request(m_settings);
    }
}

void OPLinkModemSession::requestAll(UAVObject *obj)
{
    if (!m_open) {
        return;
    }
    if (m_private) {
        m_talk->sendObjectRequest(obj, true);
    } else {
        // straight through the link: the telemetry queue would hold the next
        // request until this one's transaction times out
        ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
        TelemetryManager *tm = pm->getObject<TelemetryManager>();
        if (tm && tm->uavTalk()) {
            tm->uavTalk()->sendObjectRequest(obj, true);
        } else {
            obj->requestUpdateAll();
        }
    }
}

void OPLinkModemSession::saveSettings()
{
    ObjectPersistence::DataFields d = m_persistence->getData();
    d.Operation  = ObjectPersistence::OPERATION_SAVE;
    d.Selection  = ObjectPersistence::SELECTION_SINGLEOBJECT;
    d.ObjectID   = m_settings->getObjID();
    d.InstanceID = 0;
    m_persistence->setData(d);
    send(m_persistence);
}

void OPLinkModemSession::reboot()
{
    // FirmwareIAP on the modem: 1122, 2233, then 4455 resets it straight back
    // into its firmware (3344 would park it in the bootloader for an upload)
    if (m_rebootStage >= 0) {
        return;
    }
    m_rebootStage = 0;
    request(m_iap);
    m_rebootTimer->start(REBOOT_STEP_MS);
}

void OPLinkModemSession::rebootStep()
{
    static const quint16 steps[3] = { IAP_STEP_1, IAP_STEP_2, IAP_STEP_3_REBOOT };

    if (m_rebootStage < 0 || m_rebootStage > 2 || !m_open) {
        m_rebootTimer->stop();
        m_rebootStage = -1;
        return;
    }
    FirmwareIAPObj::DataFields d = m_iap->getData();
    d.Command   = steps[m_rebootStage];
    d.BoardType = OPLINK_BOARD_TYPE;
    m_iap->setData(d);
    send(m_iap);
    if (++m_rebootStage > 2) {
        m_rebootTimer->stop();
        m_rebootStage = -1;
    }
}

/* -------------------------------------------------------------------- panel */

OPLinkModemPanel::OPLinkModemPanel(OPLinkModemSession *session, QWidget *parent) :
    QGroupBox(parent), m_session(session), m_settingsSeen(false),
    m_testSentAt(0), m_testPending(false), m_knownDeviceId(0), m_testSentCount(0), m_testReplies(0), m_testRttSum(0), m_testRttMax(0)
{
    setTitle(QString("%1  %2%3").arg(session->product()).arg(session->serial().left(24))
             .arg(session->isPrivate() ? "" : tr("  (the GCS connection)")));

    QVBoxLayout *v = new QVBoxLayout(this);
    m_include  = new QCheckBox(tr("Include in the auto-configuration"));
    m_include->setChecked(true);
    v->addWidget(m_include);
    m_identity = new QLabel(tr("Device ID: waiting for the modem"));
    m_role     = new QLabel("");
    m_link     = new QLabel("");
    m_pairs    = new QLabel("");
    m_firmware = new QLabel("");
    m_firmware->setWordWrap(true);
    v->addWidget(m_identity);
    v->addWidget(m_role);
    v->addWidget(m_link);
    v->addWidget(m_pairs);
    v->addWidget(m_firmware);

    QGridLayout *g = new QGridLayout();
    int row = 0;
    m_coordinator = new QCheckBox(tr("Coordinator"));
    g->addWidget(m_coordinator, row, 0, 1, 2);
    ++row;
    g->addWidget(new QLabel(tr("Coordinator ID (hex)")), row, 0);
    m_coordId = new QLineEdit();
    g->addWidget(m_coordId, row, 1);
    ++row;
    g->addWidget(new QLabel(tr("Max power (mW)")), row, 0);
    m_power = new QComboBox();
    g->addWidget(m_power, row, 1);
    ++row;
    g->addWidget(new QLabel(tr("Com speed (bps)")), row, 0);
    m_speed = new QComboBox();
    g->addWidget(m_speed, row, 1);
    ++row;
    g->addWidget(new QLabel(tr("Channels")), row, 0);
    QHBoxLayout *ch = new QHBoxLayout();
    m_minChannel = new QSpinBox();
    m_minChannel->setRange(0, 250);
    m_maxChannel = new QSpinBox();
    m_maxChannel->setRange(0, 250);
    ch->addWidget(m_minChannel);
    ch->addWidget(new QLabel(".."));
    ch->addWidget(m_maxChannel);
    g->addLayout(ch, row, 1);
    ++row;
    g->addWidget(new QLabel(tr("Main port")), row, 0);
    m_mainPort = new QComboBox();
    g->addWidget(m_mainPort, row, 1);
    ++row;
    g->addWidget(new QLabel(tr("Flexi port")), row, 0);
    m_flexiPort = new QComboBox();
    g->addWidget(m_flexiPort, row, 1);
    ++row;
    g->addWidget(new QLabel(tr("VCP port")), row, 0);
    m_vcpPort = new QComboBox();
    g->addWidget(m_vcpPort, row, 1);
    v->addLayout(g);

    QHBoxLayout *b = new QHBoxLayout();
    m_applyButton  = new QPushButton(tr("Apply"));
    m_saveButton   = new QPushButton(tr("Save"));
    m_rebootButton = new QPushButton(tr("Reboot"));
    m_testButton   = new QPushButton(tr("Test link"));
    b->addWidget(m_applyButton);
    b->addWidget(m_saveButton);
    b->addWidget(m_rebootButton);
    b->addWidget(m_testButton);
    v->addLayout(b);
    m_saveResult = new QLabel(tr("Settings take effect after a reboot."));
    m_saveResult->setWordWrap(true);
    m_testResult = new QLabel(tr("Link test not run"));
    m_testResult->setWordWrap(true);
    v->addWidget(m_saveResult);
    v->addWidget(m_testResult);
    v->addStretch();

    fillCombo(m_power, "MaxRFPower");
    fillCombo(m_speed, "ComSpeed");
    fillCombo(m_mainPort, "MainPort");
    fillCombo(m_flexiPort, "FlexiPort");
    fillCombo(m_vcpPort, "VCPPort");

    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(save()));
    connect(m_rebootButton, SIGNAL(clicked()), this, SLOT(reboot()));
    connect(m_testButton, SIGNAL(clicked()), this, SLOT(startLinkTest()));
    connect(m_session->status(), SIGNAL(objectUpdated(UAVObject *)), this, SLOT(refreshStatus()));
    connect(m_session->settings(), SIGNAL(objectUnpacked(UAVObject *)), this, SLOT(refreshSettings()));
    connect(m_session->persistence(), SIGNAL(objectUnpacked(UAVObject *)), this, SLOT(persistenceUpdated(UAVObject *)));
    connect(m_session->status(), SIGNAL(objectUnpacked(UAVObject *)), this, SLOT(linkTestReply(UAVObject *)));

    m_testTimer = new QTimer(this);
    connect(m_testTimer, SIGNAL(timeout()), this, SLOT(linkTestTick()));

    refreshStatus();
    // the form fills itself when the first OPLinkSettings arrives from the modem
}

void OPLinkModemPanel::fillCombo(QComboBox *combo, const QString &fieldName)
{
    UAVObjectField *f = m_session->settings()->getField(fieldName);

    combo->clear();
    if (f) {
        combo->addItems(f->getOptions());
    }
}

quint32 OPLinkModemPanel::deviceId() const
{
    return m_session->status()->getData().DeviceID;
}

bool OPLinkModemPanel::isIncluded() const
{
    return m_include->isChecked();
}

void OPLinkModemPanel::setRole(bool coordinator, quint32 coordId)
{
    m_coordinator->setChecked(coordinator);
    m_coordId->setText(coordinator ? "0" : QString::number(coordId, 16).toUpper());
}

void OPLinkModemPanel::setPorts(const QString &mainPort, const QString &flexiPort, const QString &vcpPort)
{
    m_mainPort->setCurrentIndex(m_mainPort->findText(mainPort));
    m_flexiPort->setCurrentIndex(m_flexiPort->findText(flexiPort));
    m_vcpPort->setCurrentIndex(m_vcpPort->findText(vcpPort));
}

void OPLinkModemPanel::setRadio(const QString &power, const QString &speed, int minChannel, int maxChannel)
{
    m_power->setCurrentIndex(m_power->findText(power));
    m_speed->setCurrentIndex(m_speed->findText(speed));
    m_minChannel->setValue(minChannel);
    m_maxChannel->setValue(maxChannel);
}

void OPLinkModemPanel::refreshStatus()
{
    OPLinkStatus::DataFields s = m_session->status()->getData();

    // the far modem's answers to a link test arrive in this same object
    if (m_knownDeviceId == 0 && s.DeviceID) {
        m_knownDeviceId = s.DeviceID;
    }
    if (m_knownDeviceId && s.DeviceID && s.DeviceID != m_knownDeviceId) {
        return;
    }
    UAVObjectField *linkField  = m_session->status()->getField("LinkState");
    QString state = linkField ? linkField->getValue().toString() : "?";

    if (s.DeviceID == 0 && state == "Disabled") {
        m_identity->setText(tr("Device ID: radio off (Max power is 0)"));
    } else {
        m_identity->setText(tr("Device ID: %1").arg(QString::number(s.DeviceID, 16).toUpper()));
    }
    m_link->setText(tr("Link: %1   quality %2   tx %3 B/s   rx %4 B/s   heap %5   resets %6")
                    .arg(state).arg(s.LinkQuality).arg(s.TXRate).arg(s.RXRate).arg(s.HeapRemaining).arg(s.Resets));
    // The pair table: on a remote, the coordinator it hears; on the coordinator,
    // the remotes it hears (their keepalives carry their id).
    bool coordinator = m_session->settings()->getData().Coordinator == OPLinkSettings::COORDINATOR_TRUE;
    QStringList pairs;
    int best = -127;
    for (unsigned int i = 0; i < OPLinkStatus::PAIRIDS_NUMELEM; ++i) {
        if (s.PairIDs[i]) {
            pairs << QString("%1 at %2 dBm").arg(QString::number(s.PairIDs[i], 16).toUpper()).arg((int)s.PairSignalStrengths[i]);
            best = qMax(best, (int)s.PairSignalStrengths[i]);
        }
    }
    if (coordinator) {
        // remotes announce their id in their keepalives, so these are real remote ids
        if (pairs.isEmpty()) {
            m_pairs->setText(tr("Hears: no remote (nothing received for a few seconds)"));
        } else if (pairs.size() == 1) {
            m_pairs->setText(tr("Hears remote %1").arg(pairs.first()));
        } else {
            m_pairs->setText(tr("Hears %1 remotes: %2").arg(pairs.size()).arg(pairs.join(", ")));
        }
    } else {
        m_pairs->setText(tr("Hears: %1").arg(pairs.isEmpty() ? tr("no coordinator") : pairs.join(", ")));
    }
    if (s.Description[0] == 'O' && s.Description[1] == 'p') {
        QByteArray tag;
        for (int i = 14; i < 40; ++i) {
            if (!s.Description[i]) {
                break;
            }
            tag.append((char)s.Description[i]);
        }
        m_firmware->setText(tr("Firmware %1, board type %2 rev %3").arg(QString(tag)).arg(s.BoardType).arg(s.BoardRevision));
    }
}

void OPLinkModemPanel::refreshSettings()
{
    OPLinkSettings *o = m_session->settings();
    OPLinkSettings::DataFields d = o->getData();

    if (d.Coordinator == OPLinkSettings::COORDINATOR_TRUE) {
        m_role->setText(tr("Role: COORDINATOR (sets the hop sequence and the time base; remotes bind to its Device ID)"));
    } else if (d.CoordID) {
        m_role->setText(tr("Role: remote, bound to coordinator %1").arg(QString::number(d.CoordID, 16).toUpper()));
    } else {
        m_role->setText(tr("Role: remote, not bound to any coordinator"));
    }
    if (m_settingsSeen) {
        return; // keep the user's edits; the next Apply writes them
    }
    if (!o->getField("MaxRFPower") || !o->getField("MaxRFPower")->getOptions().size()) {
        return;
    }
    m_settingsSeen = true;
    m_coordinator->setChecked(d.Coordinator == OPLinkSettings::COORDINATOR_TRUE);
    m_coordId->setText(QString::number(d.CoordID, 16).toUpper());
    m_power->setCurrentIndex(m_power->findText(o->getField("MaxRFPower")->getValue().toString()));
    m_speed->setCurrentIndex(m_speed->findText(o->getField("ComSpeed")->getValue().toString()));
    m_minChannel->setValue(d.MinChannel);
    m_maxChannel->setValue(d.MaxChannel);
    m_mainPort->setCurrentIndex(m_mainPort->findText(o->getField("MainPort")->getValue().toString()));
    m_flexiPort->setCurrentIndex(m_flexiPort->findText(o->getField("FlexiPort")->getValue().toString()));
    m_vcpPort->setCurrentIndex(m_vcpPort->findText(o->getField("VCPPort")->getValue().toString()));
}

void OPLinkModemPanel::writeForm()
{
    OPLinkSettings *o = m_session->settings();
    OPLinkSettings::DataFields d = o->getData();
    bool ok = false;

    d.Coordinator = m_coordinator->isChecked() ? OPLinkSettings::COORDINATOR_TRUE : OPLinkSettings::COORDINATOR_FALSE;
    d.CoordID     = m_coordId->text().trimmed().toUInt(&ok, 16);
    if (!ok) {
        d.CoordID = 0;
    }
    d.MinChannel = m_minChannel->value();
    d.MaxChannel = m_maxChannel->value();
    // every field goes in one setData: the GCS telemetry layer transmits the
    // object the moment it changes and ignores a second write while that one
    // is in flight, so a field set afterwards would never reach the modem
    d.MaxRFPower = o->getField("MaxRFPower")->getOptions().indexOf(m_power->currentText());
    d.ComSpeed   = o->getField("ComSpeed")->getOptions().indexOf(m_speed->currentText());
    d.MainPort   = o->getField("MainPort")->getOptions().indexOf(m_mainPort->currentText());
    d.FlexiPort  = o->getField("FlexiPort")->getOptions().indexOf(m_flexiPort->currentText());
    d.VCPPort    = o->getField("VCPPort")->getOptions().indexOf(m_vcpPort->currentText());
    o->setData(d);
}

void OPLinkModemPanel::apply()
{
    writeForm();
    m_session->send(m_session->settings());
    m_saveResult->setText(tr("Applied (not saved). Settings take effect after a reboot."));
}

void OPLinkModemPanel::save()
{
    writeForm();
    m_session->send(m_session->settings());
    m_session->saveSettings();
    m_saveResult->setText(tr("Saving..."));
}

void OPLinkModemPanel::persistenceUpdated(UAVObject *object)
{
    Q_UNUSED(object);
    ObjectPersistence::DataFields d = m_session->persistence()->getData();
    if (d.ObjectID != m_session->settings()->getObjID()) {
        return;
    }
    if (d.Operation == ObjectPersistence::OPERATION_COMPLETED) {
        m_saveResult->setText(tr("Saved. Reboot to make it take effect."));
    } else if (d.Operation == ObjectPersistence::OPERATION_ERROR) {
        m_saveResult->setText(tr("The modem reported an error saving."));
    }
}

void OPLinkModemPanel::reboot()
{
    m_saveResult->setText(tr("Rebooting: the modem drops off USB for a few seconds and this panel comes back."));
    m_session->reboot();
}

void OPLinkModemPanel::startLinkTest()
{
    if (m_testTimer->isActive()) {
        return;
    }
    m_testReplies   = 0;
    m_testSentCount = 0;
    m_testRttSum    = 0;
    m_testRttMax    = 0;
    m_testPending   = false;
    m_testClock.start();
    m_testButton->setEnabled(false);
    m_testResult->setText(tr("Testing..."));
    m_testTimer->start(LINKTEST_PERIOD_MS);
    linkTestTick();
}

void OPLinkModemPanel::linkTestTick()
{
    if (m_testSentCount >= LINKTEST_COUNT) {
        m_testTimer->stop();
        QTimer::singleShot(LINKTEST_SETTLE_MS, this, SLOT(finishLinkTest()));
        return;
    }
    ++m_testSentCount;
    m_testPending = true;
    m_testSentAt  = m_testClock.elapsed();
    m_session->requestAll(m_session->status());
}

void OPLinkModemPanel::linkTestReply(UAVObject *object)
{
    Q_UNUSED(object);
    if (!m_testPending) {
        return;
    }
    OPLinkStatus::DataFields d = m_session->status()->getData();
    if (d.DeviceID == 0 || d.DeviceID == m_knownDeviceId) {
        return;
    }
    m_testPending = false;
    double rtt = m_testClock.elapsed() - m_testSentAt;
    ++m_testReplies;
    m_testRttSum += rtt;
    m_testRttMax  = qMax(m_testRttMax, rtt);
    UAVObjectField *f = m_session->status()->getField("LinkState");
    QString state     = f ? f->getValue().toString() : "?";
    m_testResult->setText(tr("Testing... %1 replies from %2 (%3, hears us at %4 dBm)")
                          .arg(m_testReplies).arg(QString::number(d.DeviceID, 16).toUpper()).arg(state).arg((int)d.PairSignalStrengths[0]));
}

void OPLinkModemPanel::finishLinkTest()
{
    if (m_testReplies > 0) {
        m_testResult->setText(tr("Link test: %1/%2 round trips, %3 lost, mean %4 ms, max %5 ms")
                              .arg(m_testReplies).arg(LINKTEST_COUNT).arg(LINKTEST_COUNT - m_testReplies)
                              .arg((int)(m_testRttSum / m_testReplies)).arg((int)m_testRttMax));
    } else {
        m_testResult->setText(tr("Link test: no reply from the far modem (%1 sent)").arg(LINKTEST_COUNT));
    }
    m_testButton->setEnabled(true);
}

/* --------------------------------------------------------------------- page */

ConfigOPLinkModemsWidget::ConfigOPLinkModemsWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *v = new QVBoxLayout(this);

    m_note = new QLabel(tr("Every OPLink on USB gets its own panel. The modem the GCS is connected to "
                           "keeps using that connection; the others are opened directly. "
                           "Settings take effect when a modem reboots."));
    m_note->setWordWrap(true);
    v->addWidget(m_note);

    QHBoxLayout *pairRow = new QHBoxLayout();
    pairRow->addWidget(new QLabel(tr("Pair: coordinator")));
    m_coordinatorChooser = new QComboBox();
    pairRow->addWidget(m_coordinatorChooser);
    pairRow->addWidget(new QLabel(tr("power")));
    m_pairPower = new QComboBox();
    pairRow->addWidget(m_pairPower);
    pairRow->addWidget(new QLabel(tr("speed")));
    m_pairSpeed = new QComboBox();
    pairRow->addWidget(m_pairSpeed);
    m_pairButton = new QPushButton(tr("Auto-configure the checked modems (save + reboot)"));
    pairRow->addWidget(m_pairButton);
    pairRow->addStretch();
    v->addLayout(pairRow);

    m_panelsLayout = new QHBoxLayout();
    v->addLayout(m_panelsLayout);
    v->addStretch();

    connect(m_pairButton, SIGNAL(clicked()), this, SLOT(autoConfigure()));

    m_rescanTimer = new QTimer(this);
    m_rescanTimer->setSingleShot(true);
    connect(m_rescanTimer, SIGNAL(timeout()), this, SLOT(rescan()));
    connect(USBMonitor::instance(), SIGNAL(deviceDiscovered()), this, SLOT(scheduleRescan()));
    connect(USBMonitor::instance(), SIGNAL(deviceRemoved()), this, SLOT(scheduleRescan()));
    Core::ConnectionManager *cm = Core::ICore::instance()->connectionManager();
    connect(cm, SIGNAL(deviceAboutToConnect(QString)), this, SLOT(releaseDevice(QString)));
    connect(cm, SIGNAL(deviceConnected(QIODevice *)), this, SLOT(scheduleRescan()));
    connect(cm, SIGNAL(deviceDisconnected()), this, SLOT(scheduleRescan()));

    rescan();
}

ConfigOPLinkModemsWidget::~ConfigOPLinkModemsWidget()
{
    foreach(OPLinkModemPanel * p, m_panels) {
        p->session()->close();
    }
}

QList<QPair<QString, QString> > ConfigOPLinkModemsWidget::modemsOnUsb()
{
    QList<QPair<QString, QString> > out;
    QList<USBPortInfo> ports = USBMonitor::instance()->availableDevices(USBMonitor::idVendor_OpenPilot, -1, -1, USBMonitor::Running);
    foreach(const USBPortInfo &p, ports) {
        if (p.product.contains("OPLink", Qt::CaseInsensitive) || p.product.contains("PipX", Qt::CaseInsensitive)) {
            bool dup = false;
            for (int i = 0; i < out.size(); ++i) {
                if (out[i].first == p.serialNumber) {
                    dup = true;
                }
            }
            if (!dup) {
                out.append(qMakePair(p.serialNumber, p.product));
            }
        }
    }
    return out;
}

void ConfigOPLinkModemsWidget::scheduleRescan()
{
    m_rescanTimer->start(1500);
}

void ConfigOPLinkModemsWidget::sessionClosed()
{
    scheduleRescan();
}

void ConfigOPLinkModemsWidget::releaseDevice(const QString &deviceName)
{
    // the Connections box is about to open this modem itself: let go of it first
    foreach(OPLinkModemPanel * p, m_panels) {
        if (p->session()->isPrivate() && p->session()->serial() == deviceName) {
            p->session()->close();
        }
    }
    scheduleRescan();
}

void ConfigOPLinkModemsWidget::rescan()
{
    QList<QPair<QString, QString> > modems = modemsOnUsb();
    Core::ConnectionManager *cm = Core::ICore::instance()->connectionManager();
    QString connectedSerial = cm->isConnected() ? cm->getCurrentDevice().device.name : "";

    // drop panels whose modem is gone or whose role (GCS connection / private) changed
    for (int i = m_panels.size() - 1; i >= 0; --i) {
        OPLinkModemPanel *p = m_panels[i];
        bool present = false;
        for (int j = 0; j < modems.size(); ++j) {
            if (modems[j].first == p->session()->serial()) {
                present = true;
            }
        }
        bool roleOk = p->session()->isPrivate() == (p->session()->serial() != connectedSerial);
        if (!present || !roleOk || !p->session()->isOpen()) {
            p->session()->close();
            m_panelsLayout->removeWidget(p);
            m_panels.removeAt(i);
            p->session()->deleteLater();
            p->deleteLater();
        }
    }
    // add panels for new modems
    for (int j = 0; j < modems.size(); ++j) {
        bool have = false;
        foreach(OPLinkModemPanel * p, m_panels) {
            if (p->session()->serial() == modems[j].first) {
                have = true;
            }
        }
        if (have) {
            continue;
        }
        OPLinkModemSession *s;
        if (modems[j].first == connectedSerial) {
            ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
            s = new OPLinkModemSession(pm->getObject<UAVObjectManager>(), modems[j].first, modems[j].second, this);
        } else {
            s = new OPLinkModemSession(modems[j].first, modems[j].second, this);
        }
        if (!s->open()) {
            delete s;
            continue;
        }
        connect(s, SIGNAL(closed()), this, SLOT(sessionClosed()));
        OPLinkModemPanel *p = new OPLinkModemPanel(s, this);
        m_panels.append(p);
        m_panelsLayout->addWidget(p);
    }
    m_coordinatorChooser->clear();
    m_coordinatorChooser->addItem(tr("automatic (the GCS's modem, else the first)"), QString());
    foreach(OPLinkModemPanel * p, m_panels) {
        m_coordinatorChooser->addItem(p->session()->serial().left(8) + (p->session()->isPrivate() ? "..." : "... (GCS side)"), p->session()->serial());
    }
    if (m_pairPower->count() == 0 && !m_panels.isEmpty()) {
        UAVObjectField *f = m_panels[0]->session()->settings()->getField("MaxRFPower");
        if (f) {
            m_pairPower->addItems(f->getOptions());
            m_pairPower->setCurrentIndex(m_pairPower->findText("1.25"));
        }
        f = m_panels[0]->session()->settings()->getField("ComSpeed");
        if (f) {
            m_pairSpeed->addItems(f->getOptions());
            m_pairSpeed->setCurrentIndex(m_pairSpeed->findText("57600"));
        }
    }
    m_pairButton->setEnabled(m_panels.size() >= 2);
    m_note->setText(m_panels.size() < 2
                    ? tr("%1 modem(s) on USB. Plug in at least two to configure a link here.").arg(m_panels.size())
                    : tr("%1 modems on USB. Auto-configure makes one the coordinator (the GCS's own modem unless you pick another) "
                         "and binds every other checked modem to it as a remote, same power, speed and channels; "
                         "all of them are saved and rebooted and the links show up in the panels within a few seconds.").arg(m_panels.size()));
}

void ConfigOPLinkModemsWidget::autoConfigure()
{
    QList<OPLinkModemPanel *> chosen;
    foreach(OPLinkModemPanel * p, m_panels) {
        if (p->isIncluded()) {
            chosen.append(p);
        }
    }
    if (chosen.size() < 2) {
        m_note->setText(tr("Check at least two modems to configure a link."));
        return;
    }
    // the coordinator: the one picked, else the GCS's own modem (it is the ground
    // side by definition), else the first checked one
    QString pick = m_coordinatorChooser->currentData().toString();
    OPLinkModemPanel *coord = NULL;
    foreach(OPLinkModemPanel * p, chosen) {
        if (!pick.isEmpty() && p->session()->serial() == pick) {
            coord = p;
        }
    }
    if (!coord) {
        foreach(OPLinkModemPanel * p, chosen) {
            if (!p->session()->isPrivate()) {
                coord = p;
            }
        }
    }
    if (!coord) {
        coord = chosen.first();
    }
    if (coord->deviceId() == 0) {
        m_note->setText(tr("The coordinator's radio is off (Device ID 0): save it with a power setting and reboot it first, "
                           "its Device ID is what the remotes bind to."));
        return;
    }
    // the firmware drives one telemetry UART (Flexi overrides Main when both are
    // set), the GCS rides USB HID, the USB serial port stays off: Main carries the
    // flight controller on whichever modem ends up in the air
    int remotes = 0;
    foreach(OPLinkModemPanel * p, chosen) {
        if (p == coord) {
            p->setRole(true, 0);
        } else {
            p->setRole(false, coord->deviceId());
            ++remotes;
        }
        p->setPorts("Telemetry", "Disabled", "Disabled");
        p->setRadio(m_pairPower->currentText(), m_pairSpeed->currentText(), 0, 250);
        p->save();
    }
    foreach(OPLinkModemPanel * p, chosen) {
        QTimer::singleShot(2500, p, SLOT(reboot()));
    }
    m_note->setText(tr("Configured: %1 coordinates, %2 remote(s) bound to it. All saved and rebooting; the panels return when the modems are back on USB.")
                    .arg(QString::number(coord->deviceId(), 16).toUpper()).arg(remotes));
}
