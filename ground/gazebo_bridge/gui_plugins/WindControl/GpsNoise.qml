import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ColumnLayout {
  Layout.minimumWidth: 320
  Layout.minimumHeight: 190
  anchors.fill: parent
  anchors.margins: 10
  spacing: 6

  RowLayout {
    Label { text: "GPS position noise"; Layout.fillWidth: true }
    Label { text: GpsNoise.posNoise.toFixed(2) + " m"; font.bold: true }
  }
  Slider {
    id: posSlider
    Layout.fillWidth: true
    from: 0; to: 5; stepSize: 0.05
    value: GpsNoise.posNoise
    onMoved: GpsNoise.posNoise = value
  }

  RowLayout {
    Label { text: "GPS velocity noise"; Layout.fillWidth: true }
    Label { text: GpsNoise.velNoise.toFixed(2) + " m/s"; font.bold: true }
  }
  Slider {
    id: velSlider
    Layout.fillWidth: true
    from: 0; to: 2; stepSize: 0.02
    value: GpsNoise.velNoise
    onMoved: GpsNoise.velNoise = value
  }

  RowLayout {
    Layout.fillWidth: true
    Button {
      text: "Clean fix"
      onClicked: {
        posSlider.value = 0; GpsNoise.posNoise = 0;
        velSlider.value = 0; GpsNoise.velNoise = 0;
      }
    }
    Item { Layout.fillWidth: true }
    Label { text: "1-sigma, applied by the bridge"; font.pixelSize: 10; opacity: 0.6 }
  }
}
