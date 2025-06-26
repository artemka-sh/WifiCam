import QtQuick
import QtQuick.Controls
import WifiCamProj

//из-за смены имени с appWifiCam на WifiCam а имя проекта с WifiCam на WifiCamProj, import WifiCamProj который необходим отображается с предупреждением, но всё ок

Item {
    id: content
    anchors.fill: parent
    visible: true

    Canvas {
        id: canvas
        anchors.fill: parent
    }

}
