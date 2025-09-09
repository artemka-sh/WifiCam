// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


import QtQuick
import QtQuick.Controls
import QtQuick.Window
import MobileUI

ApplicationWindow {
    id: main
    minimumWidth: 480
    minimumHeight: 960

    flags: Qt.Window
    visibility: Window.AutomaticVisibility
    color: Theme.colorBackground
    visible: true

    MobileUI {
            id: mobile
            screenAlwaysOn: true
        }

    Loader {
        id: contentLoader
        anchors.fill: parent
        source: {
            // if (permissionHandler.status === "pending") {
            //     return "qrc:/PermissionReq.qml";
            // } else if (permissionHandler.status === "denied") {
            //     return "qrc:/permission-denied.qml";
            // } else {
            //     return "qrc:/MainContent.qml";

            // }
            return "qrc:/MainContent.qml";
        }
    }
}


