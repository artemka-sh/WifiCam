#ifndef MJPEGSERVER_H
#define MJPEGSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QBuffer>

class MJPEGServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer server;
    QTimer timer; //для отправки кадров всем клиентам
    QSet<QTcpSocket*> clients;
public:
    explicit MJPEGServer(QObject *parent = nullptr);
    void newConnection();
    void setLastFrame(const QImage &frame);
    void sendFrames();
    void handleClientDisconnected();
    void handleSocketError(QAbstractSocket::SocketError error);
    int startServer();
signals:
};

#endif // MJPEGSERVER_H












