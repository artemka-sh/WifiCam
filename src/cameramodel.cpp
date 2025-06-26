#include "cameramodel.h"
#include <QDebug>

CameraModel::CameraModel(QObject *parent) : QAbstractListModel(parent) {
    //m_cameras инициализируется автоматически
}

void CameraModel::addCameras(const QList<QCameraDevice> &cameras) {
    beginInsertRows(QModelIndex(), m_cameras.size(), m_cameras.size() + cameras.size() - 1);
    m_cameras.append(cameras);
    endInsertRows();
}

void CameraModel::removeAll() {
    beginResetModel();
    m_cameras.clear();
    endResetModel();
}

void CameraModel::push(const QCameraDevice &camera) {
    beginInsertRows(QModelIndex(), m_cameras.size(), m_cameras.size());
    m_cameras.append(camera);
    endInsertRows();
}

void CameraModel::remove(int index) {
    if (index < 0 || index >= m_cameras.size()) {
        return;
    }
    beginRemoveRows(QModelIndex(), index, index);
    m_cameras.removeAt(index);
    endRemoveRows();
}

void CameraModel::print() {
    qDebug() << "\nPrinting from CameraModel::print()";
    for (const QCameraDevice &camera : m_cameras) {
        qDebug() << "Camera:" << camera.description() << ", ID:" << camera.id();
    }
}

QVariantList CameraModel::getCamerasForQML() const {
    QVariantList camerasList;
    for (const QCameraDevice &camera : m_cameras) {
        QVariantMap cameraMap;
        cameraMap["name"] = camera.description();
        cameraMap["id"] = QString(camera.id());
        camerasList.append(cameraMap);
    }
    return camerasList;
}

int CameraModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0; // Список не имеет иерархии
    }
    return m_cameras.size();
}

QVariant CameraModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_cameras.size()) {
        return QVariant();
    }

    const QCameraDevice &camera = m_cameras[index.row()];
    switch (role) {
    case Qt::DisplayRole: // Для C++ представлений (QListView, QTableView)
    case NameRole:        // Для QML (сопоставлено с "name" в roleNames)
        return camera.description().isEmpty() ? "Unknown Camera" : camera.description();
    case IdRole:          // Для QML (сопоставлено с "id")
        return QString(camera.id());
    default:
        return QVariant();
    }
}

bool CameraModel::insertRows(int row, int count, const QModelIndex &parent) {
    if (parent.isValid() || row < 0 || row > m_cameras.size()) {
        return false;
    }
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        m_cameras.insert(row + i, QCameraDevice()); // Пустая камера как заглушка
    }
    endInsertRows();
    return true;
}

bool CameraModel::removeRows(int row, int count, const QModelIndex &parent) {
    if (parent.isValid() || row < 0 || row + count > m_cameras.size()) {
        return false;
    }
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        m_cameras.removeAt(row);
    }
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> CameraModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IdRole] = "id";
    return roles;
}
