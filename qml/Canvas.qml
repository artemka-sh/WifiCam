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



    Rectangle{

        id: head
        width: parent.width
        height: parent.height * headerHeightRatio
        color: headerColor
        anchors {
            top: parent.top
            left: parent.left
        }


        RowLayout {
            id: headerLayout
            width: parent.width
            height: parent.height
            spacing: 0

            Row {
                id: icon_row
                spacing: spacing
                leftPadding: padding

                Image {
                    id: appIco
                    width: head.height
                    height: head.height
                    sourceSize: Qt.size(iconSize, iconSize)
                    source: "qrc:/webcam.svg"
                    fillMode: Image.PreserveAspectFit
                }

                Text{
                    id: logo
                    text: "WifiCam"
                    color: textColor
                    font.pixelSize: logoFontSize
                    font.weight: Font.DemiBold
                    anchors.verticalCenter: parent.verticalCenter
                    x:50
                }



            }


            Row {
                id: switch_and_parameters_row
                width: parent.width
                height: parent.height
                layoutDirection: Qt.RightToLeft
                spacing: spacing
                rightPadding: padding

                RoundButton {
                    id: switchCameraButton1
                    width: head.height
                    height: head.height
                    anchors.verticalCenter: parent.verticalCenter


                    background: Rectangle {
                        color: "transparent"
                        radius: parent.width / 2
                    }


                    contentItem: Image {
                        id: switchCameraIcon1
                        width: parent.width * headerHeightRatio
                        height: parent.height * headerHeightRatio
                        sourceSize: Qt.size(iconSize, iconSize)
                        source: "qrc:/webcam.svg"
                        fillMode: Image.PreserveAspectFit
                        anchors.centerIn: parent
                    }
                }

                RoundButton {
                    id: switchCameraButton2
                    width: head.height
                    height: head.height
                    anchors.verticalCenter: parent.verticalCenter

                    // Прозрачный фон
                    background: Rectangle {
                        color: "transparent"
                        radius: parent.width / 2
                    }

                    // Иконка вместо текста
                    contentItem: Image {
                        id: switchCameraIcon2
                        width: parent.width * headerHeightRatio
                        height: parent.height * headerHeightRatio
                        sourceSize: Qt.size(iconSize, iconSize)
                        source: "qrc:/webcam.svg"
                        fillMode: Image.PreserveAspectFit
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }


    Button {
        id:button;
        text: "Click me suka blyat"
        anchors.centerIn: parent
        onClicked: {
            win.color = Qt.rgba(Math.random(), Math.random(), Math.random());
        }
    }


}





