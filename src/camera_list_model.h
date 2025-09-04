#ifndef CAMERA_LIST_MODEL_H
#define CAMERA_LIST_MODEL_H

#include <QAbstractListModel>
#include <QCameraDevice>
#include <QMediaDevices>

class CameraListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Роли данных для QML делегата
    enum Role {
        RoleDisplayName = Qt::UserRole + 1, // Человекочитаемое имя камеры
        RoleDeviceId                         // Строковый идентификатор устройства
    };

    // Единица данных модели
    struct CameraItem {
        QString displayName;
        QString deviceId;
    };

    explicit CameraListModel(QObject *parent = nullptr);

    // QAbstractListModel API
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;



protected:
    // Имена ролей для доступа в QML
    QHash<int, QByteArray> roleNames() const override;


private:
    QList<CameraItem> m_items;
};

#endif // CAMERA_LIST_MODEL_H
