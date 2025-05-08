import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Canvas {
    id: canvas
    anchors.fill: parent

    readonly property real headerHeightRatio: 0.07
    readonly property color headerColor: "purple"
    readonly property color textColor: "white"
    readonly property int logoFontSize: 24
    readonly property int spacing: 10
    readonly property int padding: 10
    readonly property int iconSize: 64
    readonly property color infoTextColor: "#333333"


    Header{
        id: header
    }


    ConnectInfo {
        id: connectInfo
    }


    Button {
        id:button;
        text: "Click me "
        anchors.verticalCenterOffset: 23
        anchors.horizontalCenterOffset: -248
        anchors.centerIn: parent
        onClicked: {
            header.color = Qt.rgba(Math.random(), Math.random(), Math.random());
        }
    }



}
