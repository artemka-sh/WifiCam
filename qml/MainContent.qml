import QtQuick
import QtQuick.Controls
import WifiCam

Item {
    id: content
    anchors.fill: parent
    visible: true

    Canvas {
        id: canvas
        anchors.fill: parent
    }

    // Text {
    //     anchors.top: parent.top
    //     anchors.horizontalCenter: parent.horizontalCenter
    //     text: "Canvas Loaded"
    //     color: "white"
    //     font.pixelSize: 24
    // }
}
