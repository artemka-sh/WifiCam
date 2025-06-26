import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// ПОРА ИСПОЛЬЗОВАТЬ С++ МОДЕЛЬ

    Popup {
        id: resolutionPopup
        x: (main.width - width) / 2
        y: (main.height - height) / 2
        width: 300
        height: 400
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside



            ListView {
                id: cameraList
                anchors.fill: parent
                anchors.margins: 10
                clip: true // Обрезаем элементы за пределами области
                model: cameraModel // Модель из C++
                spacing: 10

                delegate: Rectangle {
                    width: cameraList.width
                    height: 60
                    color: "white"
                    border.color: "black"
                    radius: 5

                    Text {
                        anchors.centerIn: parent
                        text: model.cameraName // Имя камеры из модели
                        font.pixelSize: 20
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Выбрана камера:", model.cameraName)
                            cameraController.selectCamera(model.cameraId) // Вызов C++ метода
                            resolutionPopup.close()
                        }
                    }
                }

                ScrollBar.vertical: ScrollBar {
                    active: true
                }
            }

    }

