import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle {

        id: infoBox
        anchors.centerIn: parent
        width: parent.width * 0.9
        height: 300
        color: "#F5F5F5"
        radius: 10 // Закруглённые углы

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 10

            // Заголовок с иконкой Wi-Fi
            RowLayout {
                Layout.fillWidth: true
                spacing: 10


                Image {
                    id: wifiIco
                    width: wifiText.height
                    height: wifiText.font.pixelSize
                    sourceSize: Qt.size(32, 32)
                    source: "qrc:/wifi.svg"
                    fillMode: Image.PreserveAspectFit

                }


                Text {
                    id: wifiText
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
                color:infoTextColor
                Layout.fillWidth: true
            }

            // Device IP
            Text {
                text: "Device IP: " + (networkInfo ? networkInfo.deviceIP : "Not available")
                font.pixelSize: 16
                color:infoTextColor
                Layout.fillWidth: true
            }

            // Порт
            Text {
                text: "WifiCam Port: 8081"
                font.pixelSize: 16
                color:infoTextColor
                Layout.fillWidth: true
            }


            // Ссылка для доступа
            Text {
                text: "IP Cam Access:\nhttp://" + (networkInfo ? networkInfo.localIP : "Not available") + ":8081/"
                font.pixelSize: 16
                color:infoTextColor
                wrapMode: Text.Wrap
                Layout.fillWidth: true
            }
        }
    }






