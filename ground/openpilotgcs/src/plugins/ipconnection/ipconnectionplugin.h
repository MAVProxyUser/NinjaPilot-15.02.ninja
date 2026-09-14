/**
 ******************************************************************************
 *
 * @file       IPconnectionplugin.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup IPConnPlugin IP Telemetry Plugin
 * @{
 * @brief IP Connection Plugin impliment telemetry over TCP/IP and UDP/IP
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

#ifndef IPconnectionPLUGIN_H
#define IPconnectionPLUGIN_H

#include "ipconnection_global.h"
#include "ipconnectionoptionspage.h"
#include "ipconnectionconfiguration.h"
#include "coreplugin/iconnection.h"
#include <extensionsystem/iplugin.h>
// #include <QtCore/QSettings>

class QAbstractSocket;
class QTcpSocket;
class QUdpSocket;
class QTimer;

#include <QHash>
#include <QDateTime>

class IConnection;

/**
 *   Define a connection via the IConnection interface
 *   Plugin will add a instance of this class to the pool,
 *   so the connection manager can use it.
 */
class IPconnection_EXPORT IPconnectionConnection : public Core::IConnection {
    Q_OBJECT

public:
    IPconnectionConnection();
    virtual ~IPconnectionConnection();

    virtual QList <Core::IConnection::device> availableDevices();
    virtual QIODevice *openDevice(const QString &deviceName);
    virtual void closeDevice(const QString &deviceName);

    virtual QString connectionName();
    virtual QString shortName();

    IPconnectionConfiguration *Config() const
    {
        return m_config;
    }
    IPconnectionOptionsPage *Optionspage() const
    {
        return m_optionspage;
    }

protected slots:
    void onEnumerationChanged();
    void onBeaconDatagram();
    void expireBeacons();

signals: // For the benefit of IPConnection
    void CreateSocket(QString HostName, int Port, bool UseTCP);
    void CloseSocket(QAbstractSocket *socket);

private:
    QAbstractSocket *ipSocket;
    IPconnectionConfiguration *m_config;
    IPconnectionOptionsPage *m_optionspage;

    /* ESP32 board discovery.
     *
     * The ESP32 targets broadcast "NINJAPILOT <ip>" on UDP 9999 once they join
     * a network, which is how tools/wifi_setup.py finds a board without any
     * USB attached. Listening for the same beacon here means a board that has
     * joined WiFi simply appears in the connection dropdown, instead of the
     * operator having to read its IP off a serial console they cannot reach on
     * this hardware and then type it into an options page.
     *
     * Entries expire: a board that has been powered off should stop being
     * offered rather than sit there looking connectable. */
    QUdpSocket *m_beaconSocket;
    QHash<QString, QDateTime> m_discovered;   // ip -> last seen
    QDateTime m_lastAnnounce;                 // last availableDevChanged we emitted
    QString m_openDeviceName;                 // device currently opened, empty if none
    QTimer *m_beaconExpiry;
    // QSettings* settings;
};

class IPconnection_EXPORT IPconnectionPlugin : public ExtensionSystem::IPlugin {
    Q_OBJECT
                          Q_PLUGIN_METADATA(IID "OpenPilot.IPconnection")

public:
    IPconnectionPlugin();
    ~IPconnectionPlugin();

    virtual bool initialize(const QStringList &arguments, QString *error_message);
    virtual void extensionsInitialized();

private:
    IPconnectionConnection *m_connection;
};

#endif // IPconnectionPLUGIN_H
