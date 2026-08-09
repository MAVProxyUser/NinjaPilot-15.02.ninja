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
    Label { text: "Wind speed"; Layout.fillWidth: true }
    Label {
      text: WindControl.windSpeed.toFixed(0) + " mph"
      font.bold: true
    }
  }
  Slider {
    id: speedSlider
    Layout.fillWidth: true
    from: 0; to: 40; stepSize: 1
    value: WindControl.windSpeed
    onMoved: WindControl.windSpeed = value
  }

  RowLayout {
    Label { text: "Wind from"; Layout.fillWidth: true }
    Label {
      text: WindControl.compass + "  (" + WindControl.windDir.toFixed(0) + "°)"
      font.bold: true
    }
  }
  Slider {
    id: dirSlider
    Layout.fillWidth: true
    from: 0; to: 359; stepSize: 5
    value: WindControl.windDir
    onMoved: WindControl.windDir = value
  }

  RowLayout {
    Layout.fillWidth: true
    Button {
      text: "Calm"
      onClicked: { speedSlider.value = 0; WindControl.windSpeed = 0; }
    }
    Item { Layout.fillWidth: true }
    Label {
      text: "direction the wind blows FROM"
      font.pixelSize: 10
      opacity: 0.6
    }
  }
}
