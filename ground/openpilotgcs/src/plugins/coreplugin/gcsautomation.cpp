#include "gcsautomation.h"
#include "modemanager.h"
#include "imode.h"
#include "icore.h"
#include "coreconstants.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonArray>
#include <QAccessible>
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QAbstractButton>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QAbstractSlider>
#include <QSpinBox>

namespace Core {
namespace Internal {

// ---- accessibility helpers -------------------------------------------------

static QString roleName(QAccessible::Role r)
{
    switch (r) {
    case QAccessible::PushButton:   return "button";
    case QAccessible::CheckBox:     return "checkbox";
    case QAccessible::RadioButton:  return "radio";
    case QAccessible::ComboBox:     return "combobox";
    case QAccessible::EditableText: return "edit";
    case QAccessible::SpinBox:      return "spinbox";
    case QAccessible::Slider:       return "slider";
    case QAccessible::MenuItem:     return "menuitem";
    case QAccessible::MenuBar:      return "menubar";
    case QAccessible::PopupMenu:    return "menu";
    case QAccessible::PageTab:      return "tab";
    case QAccessible::PageTabList:  return "tablist";
    case QAccessible::StaticText:   return "label";
    case QAccessible::Table:        return "table";
    case QAccessible::List:         return "list";
    case QAccessible::Dialog:       return "dialog";
    case QAccessible::Window:       return "window";
    case QAccessible::Client:       return "client";
    case QAccessible::Grouping:     return "group";
    case QAccessible::Graphic:      return "canvas";
    default:                        return QString("role%1").arg((int)r);
    }
}

// Serialize an accessible node (and, up to depth, its children) with an
// index PATH from the walk root so any node is addressable deterministically.
static QJsonObject nodeJson(QAccessibleInterface *iface, int depth,
                            const QJsonArray &path, int maxNodes, int *count)
{
    QJsonObject o;
    if (!iface || !iface->isValid()) {
        return o;
    }
    o["role"] = roleName(iface->role());
    o["name"] = iface->text(QAccessible::Name);
    QString desc = iface->text(QAccessible::Description);
    if (!desc.isEmpty()) o["desc"] = desc;
    QString val = iface->text(QAccessible::Value);
    if (!val.isEmpty()) o["value"] = val;
    QRect r = iface->rect();
    o["rect"] = QJsonArray{ r.x(), r.y(), r.width(), r.height() };
    QAccessible::State st = iface->state();
    QJsonArray flags;
    if (st.checked)     flags.append("checked");
    if (st.checkable)   flags.append("checkable");
    if (st.selected)    flags.append("selected");
    if (st.focused)     flags.append("focused");
    if (st.disabled)    flags.append("disabled");
    if (st.invisible)   flags.append("invisible");
    if (!flags.isEmpty()) o["state"] = flags;
    if (QAccessibleActionInterface *ai = iface->actionInterface()) {
        QJsonArray acts;
        for (const QString &a : ai->actionNames()) acts.append(a);
        if (!acts.isEmpty()) o["actions"] = acts;
    }
    o["path"] = path;
    (*count)++;
    if (depth > 0 && *count < maxNodes) {
        QJsonArray kids;
        int n = iface->childCount();
        for (int i = 0; i < n && *count < maxNodes; i++) {
            QAccessibleInterface *c = iface->child(i);
            if (!c) continue;
            QJsonArray cp = path;
            cp.append(i);
            QJsonObject cj = nodeJson(c, depth - 1, cp, maxNodes, count);
            if (!cj.isEmpty()) kids.append(cj);
        }
        if (!kids.isEmpty()) o["children"] = kids;
    }
    return o;
}

// Resolve an index-path (from the active window's accessible root) to a node.
static QAccessibleInterface *resolvePath(const QJsonArray &path)
{
    QWidget *w = QApplication::activeWindow();
    if (!w) {
        const auto tops = QApplication::topLevelWidgets();
        for (QWidget *t : tops) { if (t->isWindow() && t->isVisible()) { w = t; break; } }
    }
    if (!w) return nullptr;
    QAccessibleInterface *iface = QAccessible::queryAccessibleInterface(w);
    for (const QJsonValue &v : path) {
        if (!iface) return nullptr;
        int idx = v.toInt();
        if (idx < 0 || idx >= iface->childCount()) return nullptr;
        iface = iface->child(idx);
    }
    return iface;
}

// Depth-first search for nodes matching name/role substrings; returns paths.
static void searchTree(QAccessibleInterface *iface, const QJsonArray &path,
                       const QString &nameQ, const QString &roleQ,
                       QJsonArray *out, int maxHits, int depth)
{
    if (!iface || !iface->isValid() || out->size() >= maxHits || depth < 0) return;
    QString nm = iface->text(QAccessible::Name);
    bool nameOk = nameQ.isEmpty() || nm.contains(nameQ, Qt::CaseInsensitive);
    bool roleOk = roleQ.isEmpty() || roleName(iface->role()).contains(roleQ, Qt::CaseInsensitive);
    if (nameOk && roleOk && (!nameQ.isEmpty() || !roleQ.isEmpty())) {
        QJsonObject hit;
        hit["role"] = roleName(iface->role());
        hit["name"] = nm;
        hit["path"] = path;
        if (QAccessibleActionInterface *ai = iface->actionInterface()) {
            QJsonArray acts; for (const QString &a : ai->actionNames()) acts.append(a);
            if (!acts.isEmpty()) hit["actions"] = acts;
        }
        out->append(hit);
    }
    int n = iface->childCount();
    for (int i = 0; i < n && out->size() < maxHits; i++) {
        QAccessibleInterface *c = iface->child(i);
        if (!c) continue;
        QJsonArray cp = path; cp.append(i);
        searchTree(c, cp, nameQ, roleQ, out, maxHits, depth - 1);
    }
}

// ---- menu walk (more reliable than accessibility for lazy menus) -----------

static QMenuBar *menuBar()
{
    if (QMainWindow *mw = qobject_cast<QMainWindow *>(ICore::instance()->mainWindow())) {
        return mw->menuBar();
    }
    return nullptr;
}

static QString cleanText(const QString &t)
{
    QString s = t; s.remove('&'); return s.trimmed();
}

static QJsonArray walkMenu(QMenu *menu)
{
    QJsonArray items;
    if (!menu) return items;
    // populate lazily-built menus
    emit menu->aboutToShow();
    for (QAction *a : menu->actions()) {
        QJsonObject o;
        if (a->isSeparator()) { o["sep"] = true; items.append(o); continue; }
        o["text"] = cleanText(a->text());
        o["enabled"] = a->isEnabled();
        if (a->isCheckable()) o["checked"] = a->isChecked();
        if (!a->shortcut().isEmpty()) o["shortcut"] = a->shortcut().toString();
        if (a->menu()) o["submenu"] = walkMenu(a->menu());
        items.append(o);
    }
    return items;
}

// Find and trigger an action by "/"-separated cleaned-text path.
static bool triggerMenuPath(const QStringList &parts)
{
    QMenuBar *mb = menuBar();
    if (!mb || parts.isEmpty()) return false;
    QList<QAction *> actions = mb->actions().toVector().toList();
    QAction *found = nullptr;
    for (int level = 0; level < parts.size(); level++) {
        found = nullptr;
        for (QAction *a : actions) {
            if (cleanText(a->text()).compare(parts[level], Qt::CaseInsensitive) == 0) { found = a; break; }
        }
        if (!found) return false;
        if (level < parts.size() - 1) {
            if (!found->menu()) return false;
            emit found->menu()->aboutToShow();
            actions = found->menu()->actions();
        }
    }
    if (found) { found->trigger(); return true; }
    return false;
}

// ---- server ----------------------------------------------------------------

GcsAutomationServer::GcsAutomationServer(QObject *parent)
    : QObject(parent), m_server(nullptr) {}

GcsAutomationServer::~GcsAutomationServer() {}

bool GcsAutomationServer::start()
{
    if (qgetenv("NINJAPILOT_GCS_AUTOMATION") != "1") return false;
    QAccessible::setActive(true);
    quint16 port = 17654;
    bool ok = false;
    quint16 envp = qgetenv("NINJAPILOT_GCS_AUTOMATION_PORT").toUShort(&ok);
    if (ok && envp) port = envp;
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &GcsAutomationServer::onNewConnection);
    if (!m_server->listen(QHostAddress::LocalHost, port)) {
        qWarning("GcsAutomationServer: cannot listen on %u: %s", port,
                 qPrintable(m_server->errorString()));
        return false;
    }
    qWarning("GcsAutomationServer: listening on 127.0.0.1:%u", port);
    return true;
}

void GcsAutomationServer::onNewConnection()
{
    while (QTcpSocket *s = m_server->nextPendingConnection()) {
        connect(s, &QTcpSocket::readyRead, this, &GcsAutomationServer::onReadyRead);
        connect(s, &QTcpSocket::disconnected, s, &QObject::deleteLater);
    }
}

void GcsAutomationServer::onReadyRead()
{
    QTcpSocket *s = qobject_cast<QTcpSocket *>(sender());
    if (!s) return;
    while (s->canReadLine()) {
        QByteArray line = s->readLine().trimmed();
        if (line.isEmpty()) continue;
        QJsonParseError perr;
        QJsonDocument doc = QJsonDocument::fromJson(line, &perr);
        QJsonObject reply;
        if (perr.error != QJsonParseError::NoError || !doc.isObject()) {
            reply["ok"] = false; reply["error"] = "bad json";
        } else {
            reply = dispatch(doc.object());
        }
        s->write(QJsonDocument(reply).toJson(QJsonDocument::Compact));
        s->write("\n");
        s->flush();
    }
}

QJsonObject GcsAutomationServer::dispatch(const QJsonObject &req)
{
    QJsonObject r;
    const QString cmd = req.value("cmd").toString();

    if (cmd == "ping") {
        r["ok"] = true; r["pong"] = true; return r;
    }

    if (cmd == "workspaces") {
        QJsonArray arr;
        if (ModeManager *mm = ModeManager::instance()) {
            for (IMode *m : mm->modes()) {
                QJsonObject o; o["name"] = m->name();
                o["id"] = QString::fromLatin1(m->uniqueModeName());
                o["current"] = (mm->currentMode() == m);
                arr.append(o);
            }
        }
        r["ok"] = true; r["workspaces"] = arr; return r;
    }

    if (cmd == "workspace") {
        const QString name = req.value("name").toString();
        if (ModeManager *mm = ModeManager::instance()) {
            mm->activateModeByWorkspaceName(name);
            r["ok"] = true; r["active"] = mm->currentMode() ? mm->currentMode()->name() : "";
        } else { r["ok"] = false; r["error"] = "no mode manager"; }
        return r;
    }

    if (cmd == "menus") {
        QJsonArray arr;
        if (QMenuBar *mb = menuBar()) {
            for (QAction *a : mb->actions()) {
                QJsonObject o; o["text"] = cleanText(a->text());
                o["enabled"] = a->isEnabled();
                if (a->menu()) o["items"] = walkMenu(a->menu());
                arr.append(o);
            }
            r["ok"] = true; r["menus"] = arr;
        } else { r["ok"] = false; r["error"] = "no menu bar"; }
        return r;
    }

    if (cmd == "menu") {   // trigger a menu action by "File/Save" style path
        const QStringList parts = req.value("path").toString().split('/', Qt::SkipEmptyParts);
        r["ok"] = triggerMenuPath(parts);
        if (!r["ok"].toBool()) r["error"] = "menu path not found";
        return r;
    }

    if (cmd == "tree") {
        int depth = req.contains("depth") ? req.value("depth").toInt() : 12;
        int maxNodes = req.contains("max") ? req.value("max").toInt() : 4000;
        QWidget *w = QApplication::activeWindow();
        if (!w) { for (QWidget *t : QApplication::topLevelWidgets()) if (t->isWindow() && t->isVisible()) { w = t; break; } }
        QAccessibleInterface *root = w ? QAccessible::queryAccessibleInterface(w) : nullptr;
        int count = 0;
        if (root) { r["ok"] = true; r["tree"] = nodeJson(root, depth, QJsonArray(), maxNodes, &count); r["nodes"] = count; }
        else { r["ok"] = false; r["error"] = "no active window"; }
        return r;
    }

    if (cmd == "find") {
        QString nameQ = req.value("name").toString();
        QString roleQ = req.value("role").toString();
        int maxHits = req.contains("max") ? req.value("max").toInt() : 100;
        QWidget *w = QApplication::activeWindow();
        if (!w) { for (QWidget *t : QApplication::topLevelWidgets()) if (t->isWindow() && t->isVisible()) { w = t; break; } }
        QAccessibleInterface *root = w ? QAccessible::queryAccessibleInterface(w) : nullptr;
        QJsonArray hits;
        if (root) searchTree(root, QJsonArray(), nameQ, roleQ, &hits, maxHits, 20);
        r["ok"] = true; r["hits"] = hits; return r;
    }

    if (cmd == "do") {   // invoke an accessibility action at an index path
        QAccessibleInterface *iface = resolvePath(req.value("path").toArray());
        QString action = req.value("action").toString("Press");
        if (iface && iface->actionInterface()) {
            iface->actionInterface()->doAction(action);
            r["ok"] = true;
        } else { r["ok"] = false; r["error"] = "no node/action"; }
        return r;
    }

    if (cmd == "get") {
        QAccessibleInterface *iface = resolvePath(req.value("path").toArray());
        if (iface) { r["ok"] = true; r["name"] = iface->text(QAccessible::Name);
            r["value"] = iface->text(QAccessible::Value); r["role"] = roleName(iface->role()); }
        else { r["ok"] = false; r["error"] = "no node"; }
        return r;
    }

    if (cmd == "set") {   // set value via the real widget (combo/edit/check/spin)
        QAccessibleInterface *iface = resolvePath(req.value("path").toArray());
        QObject *obj = iface ? iface->object() : nullptr;
        QString val = req.value("value").toString();
        bool done = false;
        if (auto *cb = qobject_cast<QComboBox *>(obj)) {
            int idx = cb->findText(val, Qt::MatchContains);
            if (idx >= 0) { cb->setCurrentIndex(idx); done = true; }
        } else if (auto *le = qobject_cast<QLineEdit *>(obj)) {
            le->setText(val); done = true;
        } else if (auto *chk = qobject_cast<QCheckBox *>(obj)) {
            chk->setChecked(val == "1" || val.compare("true", Qt::CaseInsensitive) == 0); done = true;
        } else if (auto *rb = qobject_cast<QRadioButton *>(obj)) {
            rb->setChecked(true); done = true;
        } else if (auto *sld = qobject_cast<QAbstractSlider *>(obj)) {
            sld->setValue(val.toInt()); done = true;   // sliders (e.g. map zoom)
        } else if (auto *sb = qobject_cast<QSpinBox *>(obj)) {
            sb->setValue(val.toInt()); done = true;
        } else if (auto *btn = qobject_cast<QAbstractButton *>(obj)) {
            btn->click(); done = true;
        }
        r["ok"] = done; if (!done) r["error"] = "unsupported widget for set";
        return r;
    }

    r["ok"] = false; r["error"] = "unknown cmd: " + cmd;
    return r;
}

} // namespace Internal
} // namespace Core
