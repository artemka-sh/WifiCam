import QtQuick
import QtQuick.Controls

Item {
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "#ffffff"

        Text {
            anchors.centerIn: parent
            text: "Requesting permissions..."
            font.pixelSize: 24
            color: "black"
        }
    }
}
