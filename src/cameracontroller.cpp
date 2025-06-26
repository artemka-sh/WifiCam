#include "cameracontroller.h"


CameraController::CameraController(QObject *parent)
    : m_parent(parent), camera(nullptr), videoSink(new QVideoSink(this))
{
    cameras = QMediaDevices::videoInputs();

    if (cameras.isEmpty()) {
        qDebug() << "No cameras found";
        return;
    }
    qDebug() << "Found cameras:" << cameras.size();

    camera = new QCamera(cameras.first(), this);
    captureSession.setCamera(camera);
    captureSession.setVideoSink(videoSink);

    connect(videoSink, &QVideoSink::videoFrameChanged, this, &CameraController::handleVideoFrameChanged);
    connect(camera, &QCamera::errorOccurred, this, &CameraController::handleCameraError);

    model.addCameras(cameras);
    //ЗАРЕГИСТРИРОВАТЬ МОДЕЛЬ И ДОБАВИТЬ ИЗ КОНСТРУКТОРА В ПЕРЕМЕННУЮ
    static_cast<QQmlApplicationEngine*>(m_parent)->rootContext()->setContextProperty("cameraModel", &model);       // ;->rootContext()->setContextProperty("networkInfo", networkInfo);

}

CameraController::~CameraController()
{
    if (camera) {
        camera->stop();
    }
}

void CameraController::startCamera()
{
    if (camera) {
        camera->start();
        qDebug() << "Camera started";
    } else {
        qDebug() << "No camera available to start";
    }
}

QImage CameraController::getLastFrame() const
{
    QMutexLocker locker(&m_frameMutex);
    return lastFrame;
}

void CameraController::handleVideoFrameChanged(const QVideoFrame &frame)
{
    QImage image = frame.toImage();
    if (!image.isNull()) {
        lastFrame = image.scaled(1920, 1080, Qt::KeepAspectRatio);
        qDebug() << "Captured frame:" << lastFrame.size();
    } else {
        qDebug() << "Null frame received";
    }
}

void CameraController::handleCameraError(QCamera::Error error, const QString &errorString)
{
    qDebug() << "Camera error:" << error << errorString;
}
