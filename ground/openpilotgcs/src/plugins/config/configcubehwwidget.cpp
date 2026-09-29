/**
 ******************************************************************************
 *
 * @file       configcubehwwidget.cpp
 * @brief      Hardware page for the CubePilot Cube Purple on the Mini Carrier.
 *
 * The Cube reuses the Revolution's HwSettings fields for its serial ports:
 *   RV_TelemetryPort = TELEM1 (USART2)      RV_AuxPort   = TELEM2 (USART3)
 *   RV_GPSPort       = GPS1   (UART4)       CUBE_GPS2Port = GPS2  (UART8)
 *   RV_RcvrPort      = RC IN, decoded by the IO co-processor (PPM / S.Bus)
 * CAN2 is the DroneCAN ESC bus and has no setting; MAIN OUT 1-8 are the IO
 * co-processor's PWM outputs. A Spektrum satellite goes on TELEM2 = DSM.
 *
 *****************************************************************************/
#include "configcubehwwidget.h"

#include <QDebug>
#include <QStringList>
#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <extensionsystem/pluginmanager.h>
#include <coreplugin/generalsettings.h>
#include "hwsettings.h"

ConfigCubeHWWidget::ConfigCubeHWWidget(QWidget *parent) : ConfigTaskWidget(parent), m_refreshing(true)
{
    m_ui = new Ui_CubeHWWidget();
    m_ui->setupUi(this);

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    Core::Internal::GeneralSettings *settings = pm->getObject<Core::Internal::GeneralSettings>();
    if (!settings->useExpertMode()) {
        m_ui->saveTelemetryToRAM->setEnabled(false);
        m_ui->saveTelemetryToRAM->setVisible(false);
    }

    addApplySaveButtons(m_ui->saveTelemetryToRAM, m_ui->saveTelemetryToSD);

    /* the connectors, and only the connectors, of the Mini Carrier */
    addWidgetBinding("HwSettings", "RV_TelemetryPort", m_ui->cbTelem1);
    addWidgetBinding("HwSettings", "RV_AuxPort", m_ui->cbTelem2);
    addWidgetBinding("HwSettings", "RV_GPSPort", m_ui->cbGPS1);
    addWidgetBinding("HwSettings", "CUBE_GPS2Port", m_ui->cbGPS2);
    addWidgetBinding("HwSettings", "RV_RcvrPort", m_ui->cbRcvr);

    addWidgetBinding("HwSettings", "USB_HIDPort", m_ui->cbUSBHIDFunction);
    addWidgetBinding("HwSettings", "USB_VCPPort", m_ui->cbUSBVCPFunction);
    addWidgetBinding("HwSettings", "ComUsbBridgeSpeed", m_ui->cbUSBVCPSpeed);

    addWidgetBinding("HwSettings", "TelemetrySpeed", m_ui->cbTelem1TelemSpeed);
    addWidgetBinding("HwSettings", "ComUsbBridgeSpeed", m_ui->cbTelem1ComSpeed);
    addWidgetBinding("HwSettings", "TelemetrySpeed", m_ui->cbTelem2TelemSpeed);
    addWidgetBinding("HwSettings", "ComUsbBridgeSpeed", m_ui->cbTelem2ComSpeed);
    addWidgetBinding("HwSettings", "TelemetrySpeed", m_ui->cbGPS1TelemSpeed);
    addWidgetBinding("HwSettings", "GPSSpeed", m_ui->cbGPS1GPSSpeed);
    addWidgetBinding("HwSettings", "ComUsbBridgeSpeed", m_ui->cbGPS1ComSpeed);
    addWidgetBinding("HwSettings", "TelemetrySpeed", m_ui->cbGPS2TelemSpeed);
    addWidgetBinding("HwSettings", "GPSSpeed", m_ui->cbGPS2GPSSpeed);
    addWidgetBinding("HwSettings", "ComUsbBridgeSpeed", m_ui->cbGPS2ComSpeed);

    addWidgetBinding("GPSSettings", "DataProtocol", m_ui->cbGPS1GPSProtocol);
    addWidgetBinding("GPSSettings", "DataProtocol", m_ui->cbGPS2GPSProtocol);

    setupCustomCombos();

    enableControls(true);
    populateWidgets();
    refreshWidgetsValues();
    forceConnectedState();

    m_refreshing = false;
}

ConfigCubeHWWidget::~ConfigCubeHWWidget()
{}

/* Drop the enum options a connector cannot do on this carrier. Bound combos
 * are matched by option text, so removing items is safe; a board value that
 * is not in the list is added back by the refresh, which is the honest thing. */
void ConfigCubeHWWidget::keepOnly(QComboBox *cb, const QStringList &options)
{
    for (int i = cb->count() - 1; i >= 0; i--) {
        if (!options.contains(cb->itemText(i))) {
            cb->removeItem(i);
        }
    }
}

void ConfigCubeHWWidget::setupCustomCombos()
{
    connect(m_ui->cbUSBHIDFunction, SIGNAL(currentIndexChanged(int)), this, SLOT(usbHIDPortChanged(int)));
    connect(m_ui->cbUSBVCPFunction, SIGNAL(currentIndexChanged(int)), this, SLOT(usbVCPPortChanged(int)));
    connect(m_ui->cbTelem1, SIGNAL(currentIndexChanged(int)), this, SLOT(telem1Changed(int)));
    connect(m_ui->cbTelem2, SIGNAL(currentIndexChanged(int)), this, SLOT(telem2Changed(int)));
    connect(m_ui->cbGPS1, SIGNAL(currentIndexChanged(int)), this, SLOT(gps1Changed(int)));
    connect(m_ui->cbGPS2, SIGNAL(currentIndexChanged(int)), this, SLOT(gps2Changed(int)));
}

void ConfigCubeHWWidget::refreshWidgetsValues(UAVObject *obj)
{
    m_refreshing = true;
    ConfigTaskWidget::refreshWidgetsValues(obj);
    /* RC IN is the IO co-processor's PPM / S.Bus input: on or off. The other
     * RV_RcvrPort options are Revolution pin muxes that do not exist here. */
    keepOnly(m_ui->cbRcvr, QStringList() << "Disabled" << "PWM");
    /* TELEM2 has no OSD on this carrier */
    keepOnly(m_ui->cbTelem2, QStringList() << "Disabled" << "Telemetry" << "DSM" << "ComAux" << "ComBridge");
    usbVCPPortChanged(0);
    usbHIDPortChanged(0);
    telem1Changed(0);
    telem2Changed(0);
    gps1Changed(0);
    gps2Changed(0);
    m_refreshing = false;
}

void ConfigCubeHWWidget::updateObjectsFromWidgets()
{
    ConfigTaskWidget::updateObjectsFromWidgets();

    HwSettings *hwSettings = HwSettings::GetInstance(getObjectManager());
    HwSettings::DataFields data = hwSettings->getData();

    /* the GPS module follows the ports: on when either GPS connector is a GPS */
    bool gps = (m_ui->cbGPS1->currentText() == "GPS") || (m_ui->cbGPS2->currentText() == "GPS");
    data.OptionalModules[HwSettings::OPTIONALMODULES_GPS] = gps ? HwSettings::OPTIONALMODULES_ENABLED : HwSettings::OPTIONALMODULES_DISABLED;
    hwSettings->setData(data);
}

void ConfigCubeHWWidget::usbVCPPortChanged(int index)
{
    Q_UNUSED(index);
    bool bridge = m_ui->cbUSBVCPFunction->currentText() == "ComBridge";
    m_ui->lblUSBVCPSpeed->setVisible(bridge);
    m_ui->cbUSBVCPSpeed->setVisible(bridge);
    if (!m_refreshing) {
        /* HID and VCP cannot both be the telemetry link */
        if (m_ui->cbUSBVCPFunction->currentText() == "USBTelemetry" && m_ui->cbUSBHIDFunction->currentText() == "USBTelemetry") {
            m_ui->cbUSBHIDFunction->setCurrentIndex(m_ui->cbUSBHIDFunction->findText("Disabled"));
        }
    }
}

void ConfigCubeHWWidget::usbHIDPortChanged(int index)
{
    Q_UNUSED(index);
    if (!m_refreshing) {
        if (m_ui->cbUSBHIDFunction->currentText() == "USBTelemetry" && m_ui->cbUSBVCPFunction->currentText() == "USBTelemetry") {
            m_ui->cbUSBVCPFunction->setCurrentIndex(m_ui->cbUSBVCPFunction->findText("Disabled"));
        }
    }
}

/* one speed box per port, shown only when the port function needs one */
static void showSpeed(const QString &function, QLabel *lbl, QComboBox *telem, QComboBox *gps, QComboBox *com, QComboBox *proto, QLabel *lblProto)
{
    bool t = function == "Telemetry", g = function == "GPS", c = function == "ComBridge";
    if (telem) telem->setVisible(t);
    if (gps) gps->setVisible(g);
    if (com) com->setVisible(c);
    if (proto) proto->setVisible(g);
    if (lblProto) lblProto->setVisible(g);
    lbl->setVisible(t || g || c);
}

void ConfigCubeHWWidget::telem1Changed(int index)
{
    Q_UNUSED(index);
    showSpeed(m_ui->cbTelem1->currentText(), m_ui->lblTelem1Speed, m_ui->cbTelem1TelemSpeed, NULL, m_ui->cbTelem1ComSpeed, NULL, NULL);
}

void ConfigCubeHWWidget::telem2Changed(int index)
{
    Q_UNUSED(index);
    showSpeed(m_ui->cbTelem2->currentText(), m_ui->lblTelem2Speed, m_ui->cbTelem2TelemSpeed, NULL, m_ui->cbTelem2ComSpeed, NULL, NULL);
    m_ui->lblTelem2Note->setVisible(m_ui->cbTelem2->currentText() == "DSM");
}

void ConfigCubeHWWidget::gps1Changed(int index)
{
    Q_UNUSED(index);
    showSpeed(m_ui->cbGPS1->currentText(), m_ui->lblGPS1Speed, m_ui->cbGPS1TelemSpeed, m_ui->cbGPS1GPSSpeed, m_ui->cbGPS1ComSpeed, m_ui->cbGPS1GPSProtocol, m_ui->lblGPS1Protocol);
}

void ConfigCubeHWWidget::gps2Changed(int index)
{
    Q_UNUSED(index);
    showSpeed(m_ui->cbGPS2->currentText(), m_ui->lblGPS2Speed, m_ui->cbGPS2TelemSpeed, m_ui->cbGPS2GPSSpeed, m_ui->cbGPS2ComSpeed, m_ui->cbGPS2GPSProtocol, m_ui->lblGPS2Protocol);
}
