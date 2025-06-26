#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <QAbstractListModel>
#include <QCameraDevice>

class CameraModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CameraRoles {
        NameRole = Qt::UserRole + 1, // Имя камеры (description)
        IdRole                      // Идентификатор камеры (id)
    };

    explicit CameraModel(QObject *parent = nullptr);

    void addCameras(const QList<QCameraDevice> &cameras);

    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void push(const QCameraDevice &camera);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void print();
    Q_INVOKABLE QVariantList getCamerasForQML() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

protected:
    // Для QML: сопоставление ролей с именами
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<QCameraDevice> m_cameras;
};


#endif // CAMERAMODEL_H
