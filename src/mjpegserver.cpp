#include "mjpegserver.h"

MJPEGServer::MJPEGServer(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&server, &QTcpServer::newConnection, this, &MJPEGServer::newConnection);
    QObject::connect(&timer, &QTimer::timeout, this, &MJPEGServer::sendFrames);
    // Очистка при отключении
    QObject::connect(socket, &QTcpSocket::disconnected, [socket, &clients]() {
        qDebug() << "Client disconnected:" << socket->peerAddress().toString();
        clients.remove(socket);
        socket->deleteLater();
    });

    QObject::connect(socket, &QTcpSocket::errorOccurred, [socket](QAbstractSocket::SocketError error) {
        qDebug() << "Socket error:" << error;
    });
    startServer();
}


void MJPEGServer::newConnection() {
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


}



void MJPEGServer::sendFrames() {
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
}

int MJPEGServer::startServer()
{
    if (!server.listen(QHostAddress::Any, 8081)) {
        qDebug() << "Failed to listen on 8081";
        return -1;
    }
    qDebug() << "Server running on port 8081";
    timer.start(50); // ~20 FPS
}
