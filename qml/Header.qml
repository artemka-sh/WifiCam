import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
                MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Пасхалка!")
                            head.color = Qt.rgba(Math.random(), Math.random(), Math.random());
                        }
                    }
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


        Row {       //это только выглядит как говнокод, но содержит идею
            id: switch_and_parameters_row
            width: parent.width
            height: parent.height
            spacing: spacing
            rightPadding: padding
            Layout.alignment: Qt.AlignRight

            RoundButton {
                id: switchCameraButton1
                width: head.height
                height: head.height
                anchors.verticalCenter: parent.verticalCenter
                onClicked: chooseCameraPopup.open()

                background: Rectangle {
                    color: "transparent"
                    radius: parent.width / 2
                }


                contentItem: Image {
                    id: switchCameraIcon1
                    width: parent.width * headerHeightRatio
                    height: parent.height * headerHeightRatio
                    sourceSize: Qt.size(iconSize, iconSize)
                    source: "qrc:/switch_camera.svg"
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                }


            }

            RoundButton {
                id: switchCameraButton2
                width: head.height
                height: head.height
                anchors.verticalCenter: parent.verticalCenter


                background: Rectangle {
                    color: "transparent"
                    radius: parent.width / 2
                }

                contentItem: Image {
                    id: switchCameraIcon2
                    width: parent.width * headerHeightRatio
                    height: parent.height * headerHeightRatio
                    sourceSize: Qt.size(iconSize, iconSize)
                    source: "qrc:/configuration.svg"
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                }

                onClicked: {
                    head.color = Qt.rgba(Math.random(), Math.random(), Math.random());
                }
            }
        }
    }




    ChooseCameraPop {
        id: chooseCameraPopup
        objectName: "chooseCameraPopup"
    }





}
