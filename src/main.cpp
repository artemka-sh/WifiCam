#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include <QSet>
#include <QDebug>
#include <QQmlContext>
#include "networkinfo.h"
#include "mjpegserver.h"
#include "cameracontroller.h"
#include "functional"
//#include <MobileUI>

#include "clienthttpserver.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    CameraController cameraController(&engine);
    cameraController.startCamera();
    engine.rootContext()->setContextProperty("cameraController", &cameraController);

    MJPEGServer mjpegserver;
    mjpegserver.setFrameProvider(std::bind(&CameraController::getLastFrame, &cameraController));
    mjpegserver.startServer();

    qDebug() << "Camera and server started";





    NetworkInfo *networkInfo = new NetworkInfo(&engine);
    engine.rootContext()->setContextProperty("networkInfo", networkInfo);

    // PermissionHandler permissionHandler;
    // engine_context->setContextProperty("permissionHandler", &permissionHandler);

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    if (engine.rootObjects().isEmpty()) {
        qWarning() << "Cannot init QmlApplicationEngine!";
        return EXIT_FAILURE;
    }
    // Start permission check
    //permissionHandler.checkPermission();

    return app.exec();
}


























// ClientHttpServer clientResponser;
// if (!clientResponser.startServer(8088)) {
//     return -1;
// }



//////////////////////////////////////////////// ПРОСТО ДЛЯ ПРОВЕРКИ ИНТЕРФЕЙСА

// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
// #include <MobileUI>

// #include "clienthttpserver.h"

// int main(int argc, char *argv[]) {
//     QGuiApplication app(argc, argv);

//     MobileUI::registerQML();
//     QQmlApplicationEngine engine;

//     ClientHttpServer clientResponser;
//     if (!clientResponser.startServer(8088)) {
//         return -1;
//     }

//     engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

//     if (engine.rootObjects().isEmpty()) {
//         qWarning() << "Cannot init QmlApplicationEngine!";
//         return EXIT_FAILURE;
//     }

//     return app.exec();
// }



