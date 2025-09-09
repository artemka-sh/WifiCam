import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Item {
    id: preferencesPop
    x: (main.width - width) / 2
    y: (main.height - height) / 2
    width: 300
    height: 400
    //modal: true
    focus: true
    //closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside


    ListView {
        id: preferencesList
        anchors.fill: parent
        anchors.margins: 10
        clip: true
        model: cameraListModel
        spacing: 10

        delegate: Rectangle {
            width: cameraList.width
            height: 60
            color: "white"
            border.color: "black"
            radius: 5

            Text {
                anchors.centerIn: parent
                text: model.displayName
                font.pixelSize: 10
            }
            Text {
                anchors.centerIn: parent
                text: model.displayId
                font.pixelSize: 10
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Выбрана камера:", model.displayName)
                    cameraController.cameraSelected(model.deviceId)
                    chooseCameraPopup.close()
                }
            }
        }

        ScrollBar.vertical: ScrollBar {
            active: true
        }
    }

}

