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
#include "cameramodel.h"


class CameraController : public QObject
{
    Q_OBJECT
private:
    QList<QCameraDevice> cameras;
    QCamera* camera;
    QMediaCaptureSession captureSession;
    QVideoSink* videoSink;
    QImage lastFrame;
    mutable QMutex m_frameMutex;
    CameraModel model;
    QObject *m_parent;
public:
    explicit CameraController(QObject *parent = nullptr);
    ~CameraController();
    void startCamera();
    QImage getLastFrame() const;

private slots:
    void handleVideoFrameChanged(const QVideoFrame &frame);
    void handleCameraError(QCamera::Error error, const QString &errorString);
};

#endif // CAMERACONTROLLER_H
