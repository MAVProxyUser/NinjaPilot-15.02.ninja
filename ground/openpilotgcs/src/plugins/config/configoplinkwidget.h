/**
 ******************************************************************************
 *
 * @file       configpipxtremewidget.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup ConfigPlugin Config Plugin
 * @{
 * @brief The Configuration Gadget used to configure PipXtreme
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#ifndef CONFIGPIPXTREMEWIDGET_H
#define CONFIGPIPXTREMEWIDGET_H

#include <oplinksettings.h>
#include <oplinkstatus.h>
#include <QTimer>
#include <QElapsedTimer>
#include <QMap>

#include "ui_oplink.h"
#include "configtaskwidget.h"

class ConfigOPLinkWidget : public ConfigTaskWidget {
    Q_OBJECT

public:
    ConfigOPLinkWidget(QWidget *parent = 0);
    ~ConfigOPLinkWidget();

public slots:
    void updateStatus(UAVObject *object1);
    void updateSettings(UAVObject *object1);

private:
    Ui_OPLinkWidget *m_oplink;

    // The OPLink status UAVObject
    UAVDataObject *oplinkStatusObj;

    // The OPLink ssettins UAVObject
    OPLinkSettings *oplinkSettingsObj;

    // Are the settings current?
    bool settingsUpdated;
    // Link test: round trips through the modem at the far end of the radio
    quint32 linkTestNearId;
    bool linkTestPending;
    QTimer *linkTestTimer;
    QElapsedTimer linkTestClock;
    QMap<quint16, qint64> linkTestSent;
    quint16 linkTestSeq;
    int linkTestSentCount;
    int linkTestReplies;
    double linkTestRttSum;
    double linkTestRttMax;
    static const int LINKTEST_COUNT    = 20;
    static const int LINKTEST_PERIOD   = 200; // ms between requests (one in flight at a time; a hop period apart)
    static const int LINKTEST_SETTLE   = 1500; // ms to wait for the last replies

protected:
    void updateEnableControls();

private slots:
    void disconnected();
    void bind();
    void ppmOnlyChanged();
    void minChannelChanged();
    void maxChannelChanged();
    void channelChanged(bool isMax);
    void startLinkTest();
    void linkTestTick();
    void linkTestReply(UAVObject *object);
    void finishLinkTest();
};

#endif // CONFIGTXPIDWIDGET_H
