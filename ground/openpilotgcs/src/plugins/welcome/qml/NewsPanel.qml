// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import QtQuick.XmlListModel 2.0

Item {
    id: container
    width: 100
    height: 62

    signal clicked(string url)

    Text {
        id: header
        text: qsTr("Project News")
        width: parent.width
        color: "#44515c"
        font {
            pointSize: 14
            weight: Font.Bold
        }
    }

    ListView {
        id: view
        width: parent.width
        anchors { top: header.bottom; topMargin: 14; bottom: parent.bottom }
        model: xmlModel
        delegate: listDelegate
        clip: true
    }

    ScrollDecorator {
        flickableItem: view
    }

    XmlListModel {
        id: xmlModel
        // Project news = this repo's own commit history (the old WordPress
        // feed died with openpilot.org in 2015)
        source: "https://github.com/MAVProxyUser/NinjaPilot-15.02.ninja/commits/claude.atom"
        query: "/feed/entry"
        namespaceDeclarations: "declare default element namespace 'http://www.w3.org/2005/Atom';"

        // GitHub wraps the commit subject in "\n        ...\n    " and often
        // leaves author/name EMPTY (unlinked committer email) - trim the one
        // and show the commit date instead of the other, or every entry
        // renders with blank lines around it.
        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "updated"; query: "updated/string()" }
        XmlRole { name: "link"; query: "link/@href/string()" }
    }

    Component {
        id: listDelegate
        Item {
            width: view.width
            height: column.height + 8

            Column {
                id: column
                spacing: 2
                Text {
                    text: title.trim()
                    width: view.width - 4
                    elide: Text.ElideRight
                    font.bold: true
                    color: mouseArea.containsMouse ? "#224d81" : "black"
                }

                Text {
                    text: Qt.formatDate(new Date(updated), "MMM d, yyyy")
                    width: view.width - 4
                    font.pointSize: 10
                    color: mouseArea.containsMouse ? "#224d81" : "#6a737d"
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    console.log(link)
                    container.clicked(link)
                }
            }
        }
    }
}
