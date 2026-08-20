/**
 * GcsAutomationServer - a line-delimited JSON control surface for the GCS,
 * exposing the FULL interactive surface via Qt Accessibility (QAccessible)
 * plus first-class verbs for workspaces (Welcome/Flight data/Configuration/
 * System/Scopes/HITL/Firmware) and the menu bar (File/Edit/Tools/Help/...).
 *
 * Runs entirely on the GUI thread (the QTcpServer is created there, so its
 * signals fire there) - so accessibility/widget calls need no marshaling.
 * Localhost only. Enabled by NINJAPILOT_GCS_AUTOMATION=1 (port via
 * NINJAPILOT_GCS_AUTOMATION_PORT, default 17654).
 */
#ifndef GCSAUTOMATION_H
#define GCSAUTOMATION_H

#include <QObject>
#include <QJsonObject>

class QTcpServer;
class QTcpSocket;

namespace Core {
namespace Internal {

class GcsAutomationServer : public QObject {
    Q_OBJECT
public:
    explicit GcsAutomationServer(QObject *parent = nullptr);
    ~GcsAutomationServer();
    bool start();   // honors the env gate; returns true if listening

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QJsonObject dispatch(const QJsonObject &req);
    QTcpServer *m_server;
};

} // namespace Internal
} // namespace Core

#endif
