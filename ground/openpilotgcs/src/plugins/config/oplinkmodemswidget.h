/**
 ******************************************************************************
 *
 * @file       oplinkmodemswidget.h
 * @brief      Configuration page for two (or more) OPLink modems on USB at once:
 *             every modem gets its own UAVTalk session over its HID interface,
 *             so their settings can be read, edited, saved, paired and tested
 *             without a flight controller and without switching the GCS's
 *             single telemetry connection between them.
 *****************************************************************************/
#ifndef OPLINKMODEMSWIDGET_H
#define OPLINKMODEMSWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QTimer>
#include <QElapsedTimer>
#include <QMap>
#include <QList>

class QLabel;
class QCheckBox;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QPushButton;
class QHBoxLayout;

class UAVObject;
class UAVObjectManager;
class UAVTalk;
class RawHID;
class OPLinkStatus;
class OPLinkSettings;
class ObjectPersistence;
class FirmwareIAPObj;

/**
 * One modem.  Either the GCS's own connection (objects live in the global
 * object manager and go through the telemetry layer) or a private session
 * (own RawHID, own object manager, own UAVTalk).
 */
class OPLinkModemSession : public QObject {
    Q_OBJECT
public:
    // the modem the GCS is connected to
    OPLinkModemSession(UAVObjectManager *mainManager, const QString &serial, const QString &product, QObject *parent = 0);
    // any other modem on USB
    OPLinkModemSession(const QString &serial, const QString &product, QObject *parent = 0);
    ~OPLinkModemSession();

    bool open();
    void close();
    bool isOpen() const
    {
        return m_open;
    }
    bool isPrivate() const
    {
        return m_private;
    }
    QString serial() const
    {
        return m_serial;
    }
    QString product() const
    {
        return m_product;
    }

    OPLinkStatus *status() const
    {
        return m_status;
    }
    OPLinkSettings *settings() const
    {
        return m_settings;
    }
    void requestAll(UAVObject *obj);
    ObjectPersistence *persistence() const
    {
        return m_persistence;
    }

    void send(UAVObject *obj);
    void request(UAVObject *obj);
    void saveSettings();
    void reboot();

signals:
    void closed();

private slots:
    void poll();
    void rebootStep();
    void onDeviceClosed();

private:
    void bindObjects(UAVObjectManager *manager);

    bool m_private;
    bool m_open;
    QString m_serial;
    QString m_product;
    RawHID *m_hid;
    UAVObjectManager *m_manager;
    UAVTalk *m_talk;
    OPLinkStatus *m_status;
    OPLinkSettings *m_settings;
    ObjectPersistence *m_persistence;
    FirmwareIAPObj *m_iap;
    QTimer *m_pollTimer;
    QTimer *m_rebootTimer;
    int m_rebootStage;
    int m_settingsPolls;
};

/**
 * The form for one modem: identity and link on top, the settings below,
 * Apply / Save / Reboot / Test link.
 */
class OPLinkModemPanel : public QGroupBox {
    Q_OBJECT
public:
    OPLinkModemPanel(OPLinkModemSession *session, QWidget *parent = 0);

    OPLinkModemSession *session() const
    {
        return m_session;
    }
    quint32 deviceId() const;
    bool isIncluded() const;
    void setRole(bool coordinator, quint32 coordId);
    void setPorts(const QString &mainPort, const QString &flexiPort, const QString &vcpPort);
    void setRadio(const QString &power, const QString &speed, int minChannel, int maxChannel);

public slots:
    void apply();
    void save();
    void reboot();
    void startLinkTest();
    void refreshStatus();
    void refreshSettings();

private slots:
    void linkTestTick();
    void linkTestReply(UAVObject *object);
    void finishLinkTest();
    void persistenceUpdated(UAVObject *object);

private:
    void fillCombo(QComboBox *combo, const QString &fieldName);
    void writeForm();

    OPLinkModemSession *m_session;
    QCheckBox *m_include;
    QLabel *m_identity;
    QLabel *m_role;
    QLabel *m_link;
    QLabel *m_pairs;
    QLabel *m_firmware;
    QCheckBox *m_coordinator;
    QLineEdit *m_coordId;
    QComboBox *m_power;
    QComboBox *m_speed;
    QSpinBox *m_minChannel;
    QSpinBox *m_maxChannel;
    QComboBox *m_mainPort;
    QComboBox *m_flexiPort;
    QComboBox *m_vcpPort;
    QPushButton *m_applyButton;
    QPushButton *m_saveButton;
    QPushButton *m_rebootButton;
    QPushButton *m_testButton;
    QLabel *m_testResult;
    QLabel *m_saveResult;
    bool m_settingsSeen;

    QTimer *m_testTimer;
    QElapsedTimer m_testClock;
    qint64 m_testSentAt;
    bool m_testPending;
    quint32 m_knownDeviceId;
    int m_testSentCount;
    int m_testReplies;
    double m_testRttSum;
    double m_testRttMax;
};

/**
 * The page: one panel per modem on USB, a "pair" row between them.
 */
class ConfigOPLinkModemsWidget : public QWidget {
    Q_OBJECT
public:
    ConfigOPLinkModemsWidget(QWidget *parent = 0);
    ~ConfigOPLinkModemsWidget();

    // OpenPilot modems running firmware on USB right now (OPLink Mini, PipXtreme)
    static QList<QPair<QString, QString> > modemsOnUsb();

public slots:
    void rescan();
    void autoConfigure();
    void releaseDevice(const QString &deviceName);

private slots:
    void scheduleRescan();
    void sessionClosed();

private:
    QHBoxLayout *m_panelsLayout;
    QList<OPLinkModemPanel *> m_panels;
    QComboBox *m_coordinatorChooser;
    QComboBox *m_pairPower;
    QComboBox *m_pairSpeed;
    QPushButton *m_pairButton;
    QLabel *m_note;
    QTimer *m_rescanTimer;
};

#endif // OPLINKMODEMSWIDGET_H
