/**
 ******************************************************************************
 *
 * @file       configcubehwwidget.h
 * @brief      Hardware page for the CubePilot Cube Purple on the Mini Carrier:
 *             the carrier's connectors, and only those, around a picture of it.
 *
 *****************************************************************************/
#ifndef CONFIGCUBEHWWIDGET_H
#define CONFIGCUBEHWWIDGET_H

#include "ui_configcubehwwidget.h"
#include "../uavobjectwidgetutils/configtaskwidget.h"
#include "extensionsystem/pluginmanager.h"
#include "uavobjectmanager.h"
#include "uavobject.h"
#include <QWidget>
#include <QList>

class ConfigCubeHWWidget : public ConfigTaskWidget {
    Q_OBJECT

public:
    ConfigCubeHWWidget(QWidget *parent = 0);
    ~ConfigCubeHWWidget();

private:
    bool m_refreshing;
    Ui_CubeHWWidget *m_ui;
    void setupCustomCombos();
    void keepOnly(QComboBox *cb, const QStringList &options);

protected slots:
    void refreshWidgetsValues(UAVObject *obj = NULL);
    void updateObjectsFromWidgets();

private slots:
    void telem1Changed(int index);
    void telem2Changed(int index);
    void gps1Changed(int index);
    void gps2Changed(int index);
    void usbVCPPortChanged(int index);
    void usbHIDPortChanged(int index);
};

#endif // CONFIGCUBEHWWIDGET_H
