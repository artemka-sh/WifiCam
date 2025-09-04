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

    camera = std::make_unique<QCamera>(cameras.first());
    captureSession.setCamera(camera.get());
    captureSession.setVideoSink(videoSink);

    connect(videoSink, &QVideoSink::videoFrameChanged, this, &CameraController::handleVideoFrameChanged);
    connect(camera.get(), &QCamera::errorOccurred, this, &CameraController::handleCameraError);

    static_cast<QQmlApplicationEngine*>(m_parent)->rootContext()->setContextProperty("cameraListModel", &cameraListModelObject);

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
        lastFrame = image.scaled(640, 640, Qt::KeepAspectRatio);
        qDebug() << "Captured frame:" << lastFrame.size();
    } else {
        qDebug() << "Null frame received";
    }
}

void CameraController::handleCameraError(QCamera::Error error, const QString &errorString)
{
    qDebug() << "Camera error:" << error << errorString;
}


void CameraController::cameraSelected(QString deviceId)
{
    cameras = QMediaDevices::videoInputs();
    auto newCamIt = std::find_if(cameras.begin(), cameras.end(), [&deviceId](const QCameraDevice &cam)
    {
        return deviceId == cam.id();
    });
    if (newCamIt != cameras.end()) {

        // Остановить и отвязать старую
        if (camera) {
            camera->stop();
            disconnect(camera.get(), nullptr, this, nullptr);
        }
        captureSession.setCamera(nullptr); // важно: освободить устройство из сессии


        qDebug() << "Подключение новой камеры:" << newCamIt->description();
        camera = std::make_unique<QCamera>(*newCamIt);
        captureSession.setCamera(camera.get());

                                                                                          //ВРЕМЕННОЕ РЕШЕНИЕ, СОЗДАТЬ ФУНКЦИЮ SELECT CAMERA
        connect(camera.get(), &QCamera::errorOccurred, this, &CameraController::handleCameraError);

        startCamera();
    } else {
        qDebug() << "Такой камеры ненайдено";
    }


}
