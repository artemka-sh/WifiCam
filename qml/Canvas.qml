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



    Header{
        id: header
    }


    Button {
        id:button;
        text: "Click me "
        anchors.verticalCenterOffset: -179
        anchors.horizontalCenterOffset: -248
        anchors.centerIn: parent
        onClicked: {
            header.color = Qt.rgba(Math.random(), Math.random(), Math.random());
        }
    }



    Rectangle {
            id: infoBox
            anchors.centerIn: parent
            width: parent.width * 0.9 // 90% ширины окна
            height: 200
            color: "#F5F5F5" // Светлый фон
            radius: 10 // Закруглённые углы

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 10

                // Заголовок с иконкой Wi-Fi
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    // Иконка Wi-Fi (можно заменить на вашу иконку)
                    Text {
                        text: "\uE63E" // Unicode для иконки Wi-Fi (можно заменить на Image)
                        font.family: "Material Icons" // Убедитесь, что шрифт поддерживает иконки
                        font.pixelSize: 24
                        color: "#000000"
                    }

                    Text {
                        text: "WiFi"
                        font.pixelSize: 20
                        font.bold: true
                        color: "#000000"
                    }
                }

                // Информация о Wi-Fi IP
                Text {
                    text: "WiFi IP: " + (networkInfo ? networkInfo.localIP : "Not available")
                    font.pixelSize: 16
                    color: "#333333"
                    Layout.fillWidth: true
                }

                // Device IP (замените на ваш IP, если нужно)
                Text {
                    text: "Device IP: 0.0.0.0"
                    font.pixelSize: 16
                    color: "#333333"
                    Layout.fillWidth: true
                }

                // Порт
                Text {
                    text: "DroidCam Port: 8081"
                    font.pixelSize: 16
                    color: "#333333"
                    Layout.fillWidth: true
                }

                // Ссылка для доступа
                Text {
                    text: "IP Cam Access:\nhttp://" + (networkInfo ? networkInfo.localIP : "Not available") + ":8081/"
                    font.pixelSize: 16
                    color: "#333333"
                    wrapMode: Text.Wrap
                    Layout.fillWidth: true
                }
            }
        }




}
