#ifndef MJPEGSERVER_H
#define MJPEGSERVER_H

#include <QObject>

class MJPEGServer : public QObject
{
    Q_OBJECT
public:
    explicit MJPEGServer(QObject *parent = nullptr);

signals:
};

#endif // MJPEGSERVER_H
