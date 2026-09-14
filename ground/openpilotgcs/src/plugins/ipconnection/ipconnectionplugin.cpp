/**
 ******************************************************************************
 *
 * @file       IPconnectionplugin.cpp
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

// The core of this plugin has been directly copied from the serial plugin and converted to work over a TCP link instead of a direct serial link

#include "ipconnectionplugin.h"
#include <QDateTime>
#include <QHostAddress>
#include <QTimer>
#include <QUdpSocket>


#include <extensionsystem/pluginmanager.h>
#include <coreplugin/icore.h>
#include "ipconnection_internal.h"

#include <QtCore/QtPlugin>
#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include <QWaitCondition>
#include <QMutex>
#include <coreplugin/threadmanager.h>

#include <QDebug>

// Communication between IPconnectionConnection::OpenDevice() and IPConnection::onOpenDevice()
QString errorMsg;
QWaitCondition openDeviceWait;
QWaitCondition closeDeviceWait;
// QReadWriteLock dummyLock;
QMutex ipConMutex;
QAbstractSocket *ret;

IPConnection::IPConnection(IPconnectionConnection *connection) : QObject()
{
    moveToThread(Core::ICore::instance()->threadManager()->getRealTimeThread());

    QObject::connect(connection, SIGNAL(CreateSocket(QString, int, bool)),
                     this, SLOT(onOpenDevice(QString, int, bool)));
    QObject::connect(connection, SIGNAL(CloseSocket(QAbstractSocket *)),
                     this, SLOT(onCloseDevice(QAbstractSocket *)));
}

/*IPConnection::~IPConnection()
   {

   }*/

void IPConnection::onOpenDevice(QString HostName, int Port, bool UseTCP)
{
    QAbstractSocket *ipSocket;
    const int Timeout = 5 * 1000;

    ipConMutex.lock();
    if (UseTCP) {
        ipSocket = new QTcpSocket(this);
    } else {
        ipSocket = new QUdpSocket(this);
    }

    // do sanity check on hostname and port...
    if ((HostName.length() == 0) || (Port < 1)) {
        errorMsg = "Please configure Host and Port options before opening the connection";
    } else {
        // try to connect...
        ipSocket->connectToHost(HostName, Port);

        // in blocking mode so we wait for the connection to succeed
        if (ipSocket->waitForConnected(Timeout)) {
            ret = ipSocket;
            openDeviceWait.wakeAll();
            ipConMutex.unlock();
            return;
        }
        // tell user something went wrong
        errorMsg = ipSocket->errorString();
    }
    /* BUGBUG TODO - returning null here leads to segfault because some caller still calls disconnect without checking our return value properly
     * someone needs to debug this, I got lost in the calling chain.*/
    ret = NULL;
    openDeviceWait.wakeAll();
    ipConMutex.unlock();
}

void IPConnection::onCloseDevice(QAbstractSocket *ipSocket)
{
    ipConMutex.lock();
    ipSocket->close();
    delete (ipSocket);
    closeDeviceWait.wakeAll();
    ipConMutex.unlock();
}


IPConnection *connection = 0;

IPconnectionConnection::IPconnectionConnection()
{
    /* Listen for ESP32 discovery beacons. ShareAddress so this never fights
     * tools/wifi_setup.py (or a second GCS) for the port -- a beacon listener
     * that made other tools fail would be a poor trade for convenience. */
    m_beaconSocket = new QUdpSocket(this);
    /* Bind AnyIPv4 explicitly, not the default QHostAddress::Any.
     *
     * Any gives a dual-stack IPv6 socket, and on macOS/BSD an IPv4 BROADCAST
     * datagram is not delivered to one of those. The board broadcasts IPv4, so
     * the beacon arrived for a plain IPv4 listener (tools/wifi_setup.py saw it
     * fine) while the GCS sat there with a bound socket that never received
     * anything -- the most confusing kind of failure, because lsof shows the
     * port held and everything looks correct. */
    if (m_beaconSocket->bind(QHostAddress::AnyIPv4, 9999,
                             QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        connect(m_beaconSocket, SIGNAL(readyRead()), this, SLOT(onBeaconDatagram()));
    }
    m_beaconExpiry = new QTimer(this);
    connect(m_beaconExpiry, SIGNAL(timeout()), this, SLOT(expireBeacons()));
    m_beaconExpiry->start(10000);

    ipSocket = NULL;
    // create all our objects
    m_config = new IPconnectionConfiguration("IP Network Telemetry", NULL, this);
    m_config->restoresettings();

    m_optionspage = new IPconnectionOptionsPage(m_config, this);

    if (!connection) {
        connection = new IPConnection(this);
    }

    // just signal whenever we have a device event...
    QMainWindow *mw = Core::ICore::instance()->mainWindow();
    QObject::connect(mw, SIGNAL(deviceChange()),
                     this, SLOT(onEnumerationChanged()));
    QObject::connect(m_optionspage, SIGNAL(availableDevChanged()),
                     this, SLOT(onEnumerationChanged()));
}

IPconnectionConnection::~IPconnectionConnection()
{ // clean up out resources...
    if (ipSocket) {
        ipSocket->close();
        delete (ipSocket);
    }
    if (connection) {
        delete connection;
        connection = NULL;
    }
}

void IPconnectionConnection::onEnumerationChanged()
{ // no change from serial plugin
    emit availableDevChanged(this);
}


QList <Core::IConnection::device> IPconnectionConnection::availableDevices()
{
    QList <Core::IConnection::device> list;
    device d;
    if (m_config->HostName().length() > 1) {
        d.displayName = (const QString)m_config->HostName();
    } else {
        d.displayName = "Unconfigured";
    }
    d.name = (const QString)m_config->HostName();
    // we only have one "device" as defined by the configuration m_config
    list.append(d);

    /* Boards heard announcing themselves on the LAN, newest first. Named so
     * they are obviously not the manually configured entry. */
    QStringList ips = m_discovered.keys();
    ips.sort();
    foreach(const QString &ip, ips) {
        /* Deliberately NOT skipped when it equals the configured host. They are
         * different entries with different behaviour: the discovered one forces
         * UDP on port 9000 from what the board itself advertised, the
         * configured one uses whatever the options page holds. Hiding the
         * discovered entry because the IPs happen to match left the operator
         * with only the manual entry and no way to pick the board the beacon
         * had found. */
        device b;
        b.name = ip;
        b.displayName = QString("ESP32 %1 (WiFi)").arg(ip);
        /* No "UDP: " in front of this one. The transport is an implementation
         * detail of an entry that already says what the board is and how it
         * was found, and the prefix only made it harder to tell apart from the
         * manually configured entry beside it. */
        b.selfNamed   = true;
        list.append(b);
    }

    return list;
}

/**
 * @brief Handle a discovery beacon from an ESP32 board.
 *
 * Payload is "NINJAPILOT <ip>". The sender address is used rather than the
 * address in the payload -- they agree in every normal case, and where they do
 * not the one we actually received from is the one we can reach.
 */
void IPconnectionConnection::onBeaconDatagram()
{
    bool changed = false;

    while (m_beaconSocket && m_beaconSocket->hasPendingDatagrams()) {
        QByteArray buf;
        QHostAddress sender;
        buf.resize(m_beaconSocket->pendingDatagramSize());
        m_beaconSocket->readDatagram(buf.data(), buf.size(), &sender);

        if (!buf.startsWith("NINJAPILOT")) {
            continue;
        }
        QString ip = sender.toString();
        // strip any IPv4-mapped IPv6 prefix so the string matches what a user types
        if (ip.startsWith("::ffff:")) {
            ip = ip.mid(7);
        }
        if (!m_discovered.contains(ip)) {
            changed = true;
        }
        m_discovered.insert(ip, QDateTime::currentDateTime());
    }

    /* Announce on the rising edge, and then keep announcing at a low rate for
     * as long as boards are being heard.
     *
     * Edge-only was wrong. The socket listens continuously, but a board is
     * only ever "new" once, so exactly one availableDevChanged was emitted per
     * board for as long as it kept beaconing. If that single signal did not
     * result in the dropdown being rebuilt -- it arrives during plugin load,
     * where ConnectionManager::devChanged() defers it, and anything that loses
     * it there loses it for good -- the board stayed invisible until its
     * 30-second expiry, despite beacons arriving every second and a half.
     *
     * Presence is a level, not an edge, so treat it as one. Re-announcing
     * costs a dropdown rebuild, which already happens on every serial poll,
     * and it self-heals from a missed notification within ANNOUNCE_SECS. */
    const int ANNOUNCE_SECS = 5;
    const QDateTime now = QDateTime::currentDateTime();

    if (changed
        || (!m_discovered.isEmpty()
            && (m_lastAnnounce.isNull() || m_lastAnnounce.secsTo(now) >= ANNOUNCE_SECS))) {
        m_lastAnnounce = now;
        emit availableDevChanged(this);
    }
}

/**
 * @brief Drop boards that have stopped beaconing.
 *
 * Without this a board that was powered off keeps being offered, and picking it
 * produces a connection timeout that looks like a firmware fault rather than an
 * absent aircraft.
 */
void IPconnectionConnection::expireBeacons()
{
    const QDateTime cutoff = QDateTime::currentDateTime().addSecs(-30);
    bool changed = false;

    foreach(const QString &ip, m_discovered.keys()) {
        if (m_discovered.value(ip) < cutoff) {
            m_discovered.remove(ip);
            changed = true;
        }
    }
    if (changed) {
        emit availableDevChanged(this);
    }
}

QIODevice *IPconnectionConnection::openDevice(const QString &deviceName)
{
    QString HostName;
    int Port;
    bool UseTCP;
    QMessageBox msgBox;

    // get the configuration info
    HostName = m_config->HostName();
    Port     = m_config->Port();
    UseTCP   = m_config->UseTCP();

    /* A discovered board overrides the configured host: the operator picked
     * that entry in the dropdown, so connect to it and not to whatever the
     * options page happens to hold. The ESP32 firmware serves UAVTalk on 9000
     * (see pios_wifi.c WIFI_TCP_PORT), so default there rather than inheriting
     * a port meant for a different target. */
    if (!deviceName.isEmpty() && m_discovered.contains(deviceName)) {
        HostName = deviceName;
        Port     = 9000;
        /* Force UDP as well as host and port.
         *
         * Leaving the transport to whatever the options page happened to hold
         * meant a discovered board still failed to connect until the operator
         * knew to switch TCP->UDP by hand -- which defeats the entire point of
         * discovery: the beacon told us exactly where the board is and how to
         * reach it, so making someone supply the missing third field is a
         * worse experience than typing the IP in the first place.
         *
         * The ESP32 firmware serves UAVTalk on both, and UDP is the one it
         * prefers: it is connectionless, so a board that reboots mid-session
         * simply resumes, where a TCP session has to be torn down and
         * re-established. */
        UseTCP = false;
    }

    if (ipSocket) {
        // Andrew: close any existing socket... this should never occur
        ipConMutex.lock();
        emit CloseSocket(ipSocket);
        closeDeviceWait.wait(&ipConMutex);
        ipConMutex.unlock();
        ipSocket = NULL;
    }

    ipConMutex.lock();
    emit CreateSocket(HostName, Port, UseTCP);
    openDeviceWait.wait(&ipConMutex);
    ipConMutex.unlock();
    ipSocket = ret;
    if (ipSocket == NULL) {
        msgBox.setText((const QString)errorMsg);
        msgBox.exec();
    }
    return ipSocket;
}

void IPconnectionConnection::closeDevice(const QString &)
{
    if (ipSocket) {
        ipConMutex.lock();
        emit CloseSocket(ipSocket);
        closeDeviceWait.wait(&ipConMutex);
        ipConMutex.unlock();
        ipSocket = NULL;
    }
}


QString IPconnectionConnection::connectionName()
{ // updated from serial plugin
    return QString("Network telemetry port");
}

QString IPconnectionConnection::shortName()
{ // updated from serial plugin
    if (m_config->UseTCP()) {
        return QString("TCP");
    } else {
        return QString("UDP");
    }
}


IPconnectionPlugin::IPconnectionPlugin()
{ // no change from serial plugin
}

IPconnectionPlugin::~IPconnectionPlugin()
{ // manually remove the options page object
    removeObject(m_connection->Optionspage());
}

void IPconnectionPlugin::extensionsInitialized()
{
    addAutoReleasedObject(m_connection);
}

bool IPconnectionPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);
    m_connection = new IPconnectionConnection();
    // must manage this registration of child object ourselves
    // if we use an autorelease here it causes the GCS to crash
    // as it is deleting objects as the app closes...
    addObject(m_connection->Optionspage());

    return true;
}
