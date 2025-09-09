import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: cameraToolBar
    width: parent.width
    height: parent.height * headerHeightRatio
    color: "#F5F5F5"
    anchors {
        top: header.bottom
        left: parent.left
    }

    Component {
        id: cameraToolBarItemComponent
        Item {
            id: root

            property url iconSource: "qrc:/webcam.svg"
            property url disableIconSource: "qrc:/switch_camera.svg"
            property color  accentColor: "#F5F5F5"

            width: cameraToolBar.height
            height: cameraToolBar.height

            Image {
                id: toolBarItemImage
                anchors.fill: parent
                source: root.iconSource
                sourceSize: Qt.size(cameraToolBar.height, cameraToolBar.height)
                fillMode: Image.PreserveAspectFit

            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    const ds = String(root.disableIconSource); // QUrl -> string
                    if (ds.indexOf("rotate") !== -1) {
                        toolBarItemImage.rotation = toolBarItemImage.rotation === 0 ? 180 : 0
                        toolBarItemImage.mirror = true
                    } else {
                        toolBarItemImage.source =
                            toolBarItemImage.source === root.iconSource
                            ? root.disableIconSource
                            : root.iconSource
                    }
                }
            }


        }
    }

    Row {
        id: cameraToolBarRow
        spacing: 8
        leftPadding: 8

        Loader {
            id: lightCamera
            sourceComponent: cameraToolBarItemComponent
            onLoaded: {
                item.iconSource = "qrc:/flash_on-fill.svg"
                item.disableIconSource = "qrc:/flash_off.svg"
            }
        }

        Loader {
            id: rotateCameraImage
            sourceComponent: cameraToolBarItemComponent
            onLoaded: {
                item.iconSource = "qrc:/rotate_left.svg"
                item.disableIconSource = "rotate"
            }
        }

        Loader {
            id: focusCamera
            sourceComponent: cameraToolBarItemComponent
            onLoaded: {
                item.iconSource = "qrc:/center_focus_strong-fill.svg"
                item.disableIconSource = "qrc:/center_focus_strong.svg"
            }
        }


    }

    // реагируем на смену accentColor у инстанса
    Connections {
        target: toolbarItemLoader.item
        function onAccentColorChanged() {
            cameraToolBar.color = toolbarItemLoader.item.accentColor
        }
    }
}




