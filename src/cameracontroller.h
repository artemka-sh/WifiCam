#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>

class CameraController : public QObject
{
    Q_OBJECT
public:
    explicit CameraController(QObject *parent = nullptr);

signals:
};

#endif // CAMERACONTROLLER_H






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
