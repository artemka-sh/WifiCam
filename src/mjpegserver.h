#ifndef MJPEGSERVER_H
#define MJPEGSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QBuffer>
#include <QImage>
#include <functional>

class MJPEGServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer server;
    QTimer timer; //для отправки кадров всем клиентам
    QImage lastFrame;
    QSet<QTcpSocket*> clients;
    std::function<QImage()> m_frameProvider;
public:
    explicit MJPEGServer(QObject *parent = nullptr);
    virtual ~MJPEGServer();
    void newConnection();
    void sendFrames();
    void setFrameProvider(std::function<QImage()> provider);
    void handleClientDisconnected();
    void handleSocketError(QAbstractSocket::SocketError error);
    int startServer();
signals:
};

#endif // MJPEGSERVER_H












