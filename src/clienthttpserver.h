#ifndef CLIENTHTTPSERVER_H
#define CLIENTHTTPSERVER_H

#include <QObject>
#include <QHttpServer>
#include <QTcpServer>

class ClientHttpServer : public QObject {
    Q_OBJECT

public:
    explicit ClientHttpServer(QObject *parent = nullptr);
    ~ClientHttpServer();

    bool startServer(quint16 port = 8081);

private:
    QHttpServer httpServer;
    QTcpServer *tcpServer;

private slots:
    void handleError(QAbstractSocket::SocketError error);
};

#endif // CLIENTHTTPSERVER_H
