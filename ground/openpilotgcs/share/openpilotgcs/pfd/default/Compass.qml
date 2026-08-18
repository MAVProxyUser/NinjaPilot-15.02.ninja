import QtQuick 2.0
import "."

Item {
    id: sceneItem
    property variant sceneSize

    SvgElementImage {
        id: compass_fixed
        elementName: "compass-fixed"
        sceneSize: sceneItem.sceneSize

        x: Math.floor(scaledBounds.x * sceneItem.width)
        y: Math.floor(scaledBounds.y * sceneItem.height)
    }

    SvgElementImage {
        id: compass_plane
        elementName: "compass-plane"
        sceneSize: sceneItem.sceneSize

        x: Math.floor(scaledBounds.x * sceneItem.width)
        y: Math.floor(scaledBounds.y * sceneItem.height)
    }

    SvgElementImage {
        id: compass_wheel
        elementName: "compass-wheel"
        sceneSize: sceneItem.sceneSize

        x: Math.floor(scaledBounds.x * sceneItem.width)
        y: Math.floor(scaledBounds.y * sceneItem.height)

        rotation: -AttitudeState.Yaw
        transformOrigin: Item.Center

        smooth: true
    }

    SvgElementImage {
        id: compass_home
        elementName: "compass-home" // Cyan point
        sceneSize: sceneItem.sceneSize
        smooth: true

        x: Math.floor(scaledBounds.x * sceneItem.width)
        y: Math.floor(scaledBounds.y * sceneItem.height)

        property real home_degrees: 180/3.1415 * Math.atan2(TakeOffLocation.East - PositionState.East, TakeOffLocation.North - PositionState.North)

        rotation: -AttitudeState.Yaw + home_degrees
        transformOrigin: Item.Bottom
        visible: TakeOffLocation.Status == 0

    }

    SvgElementImage {
        id: compass_waypoint // Double Purple arrow
        elementName: "compass-waypoint"
        sceneSize: sceneItem.sceneSize

        x: Math.floor(scaledBounds.x * sceneItem.width)
        y: Math.floor(scaledBounds.y * sceneItem.height)

        property real course_degrees: 180/3.1415 * Math.atan2(PathDesired.End_East - PositionState.East, PathDesired.End_North - PositionState.North)

        rotation: -AttitudeState.Yaw + course_degrees
        transformOrigin: Item.Center

        smooth: true
        visible: PathDesired.End_East !== 0.0 && PathDesired.End_East !== 0.0
    }



    // NinjaPilot bench instrumentation: raw per-magnetometer heading needles
    // flanking the fused compass. Each needle is a mini N-up dial: it points
    // the way THAT mag alone says the sensor faces (tilt ignored - bench
    // convention, level board). The big rose stays the fused estimate.
    // heading = atan2(-my, mx): body x-forward / y-right, NED yaw sign.
    Item {
        id: mag_main_needle

        property variant compassBounds: svgRenderer.scaledElementBounds("pfd.svg", "compass-fixed")
        width: compassBounds.width * sceneItem.width * 0.22
        height: width * 1.3
        x: compassBounds.x * sceneItem.width - width * 1.15
        y: (compassBounds.y + compassBounds.height * 0.35) * sceneItem.height

        Text {
            id: main_arrow
            text: "➤"   // heavy arrow glyph, drawn pointing right
            color: "#40ff40"
            font.pixelSize: mag_main_needle.width * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            // glyph points right, so subtract 90 to make "up = north"
            rotation: -90 + 57.2957795 * Math.atan2(-MagSensor.y, MagSensor.x)
            transformOrigin: Item.Center
            smooth: true
        }
        Text {
            text: "main"
            color: "white"
            font.pixelSize: mag_main_needle.width * 0.38
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
        }
    }

    Item {
        id: mag_aux_needle

        property variant compassBounds: svgRenderer.scaledElementBounds("pfd.svg", "compass-fixed")
        width: compassBounds.width * sceneItem.width * 0.22
        height: width * 1.3
        x: (compassBounds.x + compassBounds.width) * sceneItem.width + width * 0.15
        y: (compassBounds.y + compassBounds.height * 0.35) * sceneItem.height

        Text {
            id: aux_arrow
            text: "➤"
            color: "#40c0ff"
            font.pixelSize: mag_aux_needle.width * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            rotation: -90 + 57.2957795 * Math.atan2(-AuxMagSensor.y, AuxMagSensor.x)
            transformOrigin: Item.Center
            smooth: true
        }
        Text {
            text: "aux"
            color: "white"
            font.pixelSize: mag_aux_needle.width * 0.38
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
        }
    }

    Item {
        id: compass_text_box

        property variant scaledBounds: svgRenderer.scaledElementBounds("pfd.svg", "compass-text")

        x: scaledBounds.x * sceneItem.width
        y: scaledBounds.y * sceneItem.height
        width: scaledBounds.width * sceneItem.width
        height: scaledBounds.height * sceneItem.height

        Text {
            id: compass_text
            text: Math.floor(AttitudeState.Yaw).toFixed()
            color: "white"
            font {
                family: pt_bold.name
                pixelSize: parent.height * 1.2
            }
            anchors.centerIn: parent
        }
    }

}
