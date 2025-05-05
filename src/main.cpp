#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QCamera>
#include <QVideoSink>
#include <QImage>
#include <QBuffer>
#include <QTimer>
#include <QSet>
#include <QDebug>
//#include <MobileUI>

#include "clienthttpserver.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Настройка камеры
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty()) {
        qDebug() << "No cameras found";
        return -1;
    }
    qDebug() << "Found cameras:" << cameras.size();

    QCamera *camera = new QCamera(cameras.first());
    QMediaCaptureSession captureSession;
    captureSession.setCamera(camera);

    QVideoSink *videoSink = new QVideoSink();
    captureSession.setVideoSink(videoSink);

    QImage lastFrame;

    QObject::connect(videoSink, &QVideoSink::videoFrameChanged, [&lastFrame](const QVideoFrame &frame) {
        QImage image = frame.toImage();
        if (!image.isNull()) {
            lastFrame = image.scaled(640, 480, Qt::KeepAspectRatio);
            qDebug() << "Captured frame:" << lastFrame.size();
        } else {
            qDebug() << "Null frame received";
        }
    });

    QObject::connect(camera, &QCamera::errorOccurred, [](QCamera::Error error, const QString &errorString) {
        qDebug() << "Camera error:" << error << errorString;
    });

    // Настройка TCP-сервера
    QTcpServer server;
    QSet<QTcpSocket*> clients; // Храним клиентов

    if (!server.listen(QHostAddress::Any, 8081)) {
        qDebug() << "Failed to listen on 8081";
        return -1;
    }
    qDebug() << "Server running on port 8081";

    // Обработка нового соединения
    QObject::connect(&server, &QTcpServer::newConnection, [&server, &clients]() {
        QTcpSocket *socket = server.nextPendingConnection();
        if (!socket) {
            qDebug() << "Failed to get socket";
            return;
        }
        qDebug() << "New client connected:" << socket->peerAddress().toString();

        // Отправка заголовков MJPEG
        socket->write(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: multipart/x-mixed-replace; boundary=myboundary\r\n"
            "Cache-Control: no-cache\r\n"
            "Connection: close\r\n"
            "\r\n"
            );
        if (!socket->flush()) {
            qDebug() << "Failed to flush headers";
            socket->deleteLater();
            return;
        }

        clients.insert(socket);

        // Очистка при отключении
        QObject::connect(socket, &QTcpSocket::disconnected, [socket, &clients]() {
            qDebug() << "Client disconnected:" << socket->peerAddress().toString();
            clients.remove(socket);
            socket->deleteLater();
        });

        QObject::connect(socket, &QTcpSocket::errorOccurred, [socket](QAbstractSocket::SocketError error) {
            qDebug() << "Socket error:" << error;
        });
    });

    // Таймер для отправки кадров всем клиентам
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&clients, &lastFrame]() {
        if (clients.isEmpty()) {
            qDebug() << "No clients connected";
            return;
        }

        if (!lastFrame.isNull()) {
            QBuffer buffer;
            buffer.open(QIODevice::WriteOnly);
            lastFrame.save(&buffer, "JPEG", 80);
            QByteArray frameData = buffer.data();

            QByteArray part =
                "--myboundary\r\n"
                "Content-Type: image/jpeg\r\n"
                "Content-Length: " + QByteArray::number(frameData.size()) + "\r\n\r\n" +
                frameData + "\r\n";

            for (QTcpSocket *socket : clients) {
                if (socket->state() == QAbstractSocket::ConnectedState) {
                    socket->write(part);
                    if (!socket->flush()) {
                        qDebug() << "Failed to flush frame for:" << socket->peerAddress().toString();
                        clients.remove(socket);
                        socket->deleteLater();
                    } else {
                        qDebug() << "Frame sent to:" << socket->peerAddress().toString() << "size:" << frameData.size();
                    }
                } else {
                    qDebug() << "Removing disconnected client:" << socket->peerAddress().toString();
                    clients.remove(socket);
                    socket->deleteLater();
                }
            }
        } else {
            qDebug() << "No frame available";
        }
    });

    timer.start(50); // ~20 FPS

    camera->start();
    qDebug() << "Camera started";


    QQmlApplicationEngine engine;



    ClientHttpServer clientResponser;
    if (!clientResponser.startServer(8088)) {
        return -1;
    }

    // PermissionHandler permissionHandler;
    // engine_context->setContextProperty("permissionHandler", &permissionHandler);


    // Load QML
    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    if (engine.rootObjects().isEmpty()) {
        qWarning() << "Cannot init QmlApplicationEngine!";
        return EXIT_FAILURE;
    }
    // Start permission check
    //permissionHandler.checkPermission();
    return app.exec();
}


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
