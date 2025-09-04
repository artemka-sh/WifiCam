#include "camera_list_model.h"
#include <QDebug>
#include <utility>

 CameraListModel:: CameraListModel(QObject *parent) : QAbstractListModel(parent) {

    auto cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty()) {
        qDebug() << "No cameras found";
        return;
    }

    for(const QCameraDevice &camera : std::as_const(cameras))
    {
        m_items.push_back({camera.description(), QString::fromUtf8(camera.id())});
    }

}


int  CameraListModel::rowCount(const QModelIndex &parent) const {

    return m_items.size();
}

QVariant  CameraListModel::data(const QModelIndex &index, int role) const {
    if (role == RoleDisplayName)
        return m_items[index.row()].displayName;
    else if (role == RoleDeviceId)
        return m_items[index.row()].deviceId;
    return {};
}


QHash<int, QByteArray> CameraListModel::roleNames() const {
    return {
        {RoleDisplayName, "displayName"},
        {RoleDeviceId, "deviceId"}
    };
}
