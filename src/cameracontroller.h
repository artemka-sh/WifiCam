#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QImage>
#include <QMutex>
#include <QDebug>
#include <QMediaDevices>
#include <QQmlApplicationEngine> //для установки контекста
#include <QQmlContext>
#include <algorithm>
#include <memory>
#include "camera_list_model.h"



class CameraController : public QObject
{
    Q_OBJECT
private:
    QObject *m_parent;
    QList<QCameraDevice> cameras;
    QMediaCaptureSession captureSession;
    QVideoSink* videoSink;
    CameraListModel cameraListModelObject;

    std::unique_ptr<QCamera> camera;
    QImage lastFrame;
    mutable QMutex m_frameMutex;    

public:
    explicit CameraController(QObject *parent = nullptr);
    ~CameraController();
    void startCamera();
    QImage getLastFrame() const;
    void setNewCamera(const QCameraDevice& device);

private slots:
    void handleVideoFrameChanged(const QVideoFrame &frame);
    void handleCameraError(QCamera::Error error, const QString &errorString);

public slots:
    void cameraSelected(QString deviceId);

};

#endif // CAMERACONTROLLER_H
