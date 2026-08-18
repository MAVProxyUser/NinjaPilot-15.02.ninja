import QtQuick 2.0

Item {
    id: container
    width: 100
    height: 62

    signal clicked(string url)

    property string issuesUrl: "https://github.com/MAVProxyUser/NinjaPilot-15.02.ninja/issues"
    property int openCount: 0
    property int closedCount: 0
    property bool loadFailed: false

    // GitHub serves no Atom feed for issues, but the JSON API lists them
    // without auth. The /issues endpoint also returns pull requests -
    // those carry a "pull_request" key and are skipped.
    Component.onCompleted: {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) {
                return;
            }
            if (xhr.status !== 200) {
                container.loadFailed = true;
                return;
            }
            var issues = JSON.parse(xhr.responseText);
            for (var i = 0; i < issues.length; i++) {
                var it = issues[i];
                if (it.pull_request) {
                    continue;
                }
                if (it.state === "open") {
                    container.openCount++;
                } else {
                    container.closedCount++;
                }
                issueModel.append({
                    title: it.title,
                    number: it.number,
                    state: it.state,
                    author: it.user ? it.user.login : "",
                    opened: Qt.formatDate(new Date(it.created_at), "MMM d, yyyy"),
                    link: it.html_url
                });
            }
        };
        xhr.open("GET", "https://api.github.com/repos/MAVProxyUser/NinjaPilot-15.02.ninja/issues?state=all&per_page=30");
        xhr.send();
    }

    Text {
        id: header
        text: qsTr("Issue Tracker") +
              (issueModel.count > 0
               ? "  — " + container.openCount + qsTr(" open") + " · " + container.closedCount + qsTr(" closed")
               : "")
        width: parent.width - 32
        elide: Text.ElideRight
        color: headerMouseArea.containsMouse ? "#224d81" : "#44515c"
        font {
            pointSize: 14
            weight: Font.Bold
        }
        MouseArea {
            id: headerMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: container.clicked(container.issuesUrl)
        }
    }

    ListModel {
        id: issueModel
    }

    ListView {
        id: view
        width: parent.width
        anchors { top: header.bottom; topMargin: 14; bottom: parent.bottom }
        model: issueModel
        clip: true

        delegate: Item {
            width: view.width
            height: column.height + 10

            Column {
                id: column
                spacing: 2
                Text {
                    text: "#" + number + "  " + title
                    width: view.width - 4
                    elide: Text.ElideRight
                    font.bold: true
                    color: itemMouseArea.containsMouse ? "#224d81" : "black"
                }
                Text {
                    text: (state === "open" ? qsTr("Open") : qsTr("Closed")) +
                          " · " + author + " · " + opened
                    width: view.width - 4
                    elide: Text.ElideRight
                    font.pointSize: 10
                    color: state === "open" ? "#1a7f37" : "#86181d"
                }
            }

            MouseArea {
                id: itemMouseArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: container.clicked(link)
            }
        }
    }

    ScrollDecorator {
        flickableItem: view
    }

    Text {
        anchors { top: header.bottom; topMargin: 14 }
        width: parent.width - 16
        wrapMode: Text.WordWrap
        visible: container.loadFailed && issueModel.count === 0
        color: fallbackMouseArea.containsMouse ? "#224d81" : "#44515c"
        font.pointSize: 11
        text: qsTr("Couldn't reach GitHub — click to open the issue tracker in your browser.")
        MouseArea {
            id: fallbackMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: container.clicked(container.issuesUrl)
        }
    }
}
