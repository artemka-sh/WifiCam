#include "clienthttpserver.h"
#include <QDebug>

ClientHttpServer::ClientHttpServer(QObject *parent) : QObject(parent), tcpServer(new QTcpServer(this)) {
    // Маршрут для корневой страницы
    httpServer.route("/", []() {
        QString html =
            "<!DOCTYPE html>"
            "<html lang=\"ru\">"
            "<head>"
            "<meta charset=\"UTF-8\">"
            "<title>Simple Qt HTTP Server</title>"
            "</head>"
            "<body>"
            "<h1>Добро пожаловать!</h1>"
            "<p>Это простая HTML-страница, возвращаемая QHttpServer.</p>"
            "</body>"
            "</html>";
        return QHttpServerResponse("text/html", html.toUtf8());
    });

    // Обработка ошибок сокета
    connect(tcpServer, &QTcpServer::acceptError, this, &ClientHttpServer::handleError);
}

ClientHttpServer::~ClientHttpServer() {
    tcpServer->close();
}

bool ClientHttpServer::startServer(quint16 port) {
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Failed to listen on port" << port << ":" << tcpServer->errorString();
        return false;
    }

    if (!httpServer.bind(tcpServer)) {
        qDebug() << "Failed to bind server";
        tcpServer->close();
        return false;
    }

    qDebug() << "Server running on port" << port;
    return true;
}

void ClientHttpServer::handleError(QAbstractSocket::SocketError error) {
    qDebug() << "TCP server error:" << error;
}
