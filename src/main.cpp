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

    CameraController cameraController;
    cameraController.startCamera();

    MJPEGServer mjpegserver;
    mjpegserver.setFrameProvider(std::bind(&CameraController::getLastFrame, &cameraController));
    mjpegserver.startServer();

    qDebug() << "Camera and server started";



    QQmlApplicationEngine engine;

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


/////////////////////////////////////////////// ПОПЫТКА СДЕЛАТЬ ЧЕРЕЗ QHTTPSERVER

// #include <QGuiApplication>
// #include <QHttpServer>
// #include <QTcpServer>
// #include <QMediaDevices>
// #include <QMediaCaptureSession>
// #include <QCamera>
// #include <QVideoSink>
// #include <QImage>
// #include <QBuffer>
// #include <QTimer>
// #include <QDebug>

// int main(int argc, char *argv[]) {
//     QGuiApplication app(argc, argv);

//     // Настройка камеры
//     const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
//     if (cameras.isEmpty()) {
//         qWarning() << "No cameras found";
//         return EXIT_FAILURE;
//     }

//     QCamera *camera = new QCamera(cameras.first());
//     QMediaCaptureSession captureSession;
//     captureSession.setCamera(camera);
//     QVideoSink *videoSink = new QVideoSink();
//     captureSession.setVideoSink(videoSink);

//     QImage lastFrame;
//     QObject::connect(videoSink, &QVideoSink::videoFrameChanged, [&lastFrame](const QVideoFrame &frame) {
//         QImage image = frame.toImage();
//         if (!image.isNull()) {
//             lastFrame = image.scaled(640, 480, Qt::KeepAspectRatio);
//             //qDebug() << "Captured frame:" << lastFrame.size();
//         } else {
//             qDebug() << "Null frame received";
//         }
//     });

//     // Настройка HTTP-сервера
//     QHttpServer httpServer;
//     httpServer.route("/mjpeg", [&lastFrame](const QHttpServerRequest &, QHttpServerResponder &responder) {
//         // Установка начальных заголовков для MJPEG
//         QHttpHeaders headers;
//         headers.append("Content-Type", "multipart/x-mixed-replace; boundary=myboundary");
//         headers.append("Cache-Control", "no-cache");
//         responder.write(headers, QHttpServerResponder::StatusCode::Ok);

//         // Заголовки для каждого кадра
//         QHttpHeaders frameHeaders;
//         frameHeaders.append("Content-Type", "image/jpeg");

//         // Таймер для отправки кадров
//         QTimer *timer = new QTimer();
//         timer->setInterval(50); // ~20 FPS
//         QObject::connect(timer, &QTimer::timeout, [timer, &lastFrame, &responder, frameHeaders]() {
//             if (lastFrame.isNull()) {
//                 qDebug() << "No frame available";
//                 return;
//             }

//             QBuffer buffer;
//             buffer.open(QIODevice::WriteOnly);
//             lastFrame.save(&buffer, "JPEG", 70);
//             QByteArray frameData = buffer.data();

//             QByteArray part =
//                 "--myboundary\r\n"
//                 "Content-Type: image/jpeg\r\n"
//                 "Content-Length: " + QByteArray::number(frameData.size()) + "\r\n\r\n" +
//                 frameData + "\r\n";

//             qDebug() << "Sending frame, size:" << frameData.size();
//             responder.write(part, frameHeaders, QHttpServerResponder::StatusCode::Ok);
//         });
//         timer->start();
//         qDebug() << "Started MJPEG stream for client";
//     });

//     // Создание и привязка QTcpServer
//     QTcpServer *tcpServer = new QTcpServer();
//     if (!tcpServer->listen(QHostAddress::Any, 8081)) {
//         qWarning() << "Failed to listen on port 8081";
//         delete tcpServer;
//         return EXIT_FAILURE;
//     }

//     if (!httpServer.bind(tcpServer)) {
//         qWarning() << "Failed to bind QHttpServer to QTcpServer";
//         delete tcpServer;
//         return EXIT_FAILURE;
//     }

//     qDebug() << "Server running on port" << tcpServer->serverPort();

//     camera->start();
//     qDebug() << "Camera started";

//     return app.exec();
// }






