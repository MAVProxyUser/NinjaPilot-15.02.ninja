import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

// Deliberately bare: the image fills the panel and nothing else is drawn.
// No topic label, no picker, no status line - that chrome is the entire
// reason this plugin exists instead of gz-gui's ImageDisplay.
Rectangle {
  id: root
  color: "#101010"
  anchors.fill: parent
  property string providerName: ""

  Image {
    id: view
    anchors.fill: parent
    fillMode: Image.PreserveAspectFit
    smooth: true
    cache: false
    source: root.providerName === "" ? "" :
            "image://" + root.providerName + "/frame?" + CameraView.frameId
  }

  // Only shown before the first frame arrives, so a black panel is not
  // mistaken for a dead camera.
  Text {
    anchors.centerIn: parent
    visible: view.status !== Image.Ready
    text: "no signal"
    color: "#666666"
    font.pixelSize: 11
  }
}
