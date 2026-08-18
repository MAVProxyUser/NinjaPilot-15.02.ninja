import QtQuick 2.0

Item {
    id: container
    width: 100
    height: 62

    signal clicked(string url)

    Text {
        id: header
        text: qsTr("Issue Tracker")
        width: parent.width - 32
        color: "#44515c"
        font {
            pointSize: 14
            weight: Font.Bold
        }
    }

    Text {
        id: body
        anchors { top: header.bottom; topMargin: 14 }
        width: parent.width - 16
        wrapMode: Text.WordWrap
        color: mouseArea.containsMouse ? "#224d81" : "#44515c"
        font.pointSize: 11
        text: qsTr("Browse and file NinjaPilot issues on GitHub.\n\n") +
              "github.com/MAVProxyUser/NinjaPilot-15.02.ninja/issues"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: container.clicked("https://github.com/MAVProxyUser/NinjaPilot-15.02.ninja/issues")
    }
}
