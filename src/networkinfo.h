#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QNetworkInterface>

class NetworkInfo : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString localIP READ localIP NOTIFY localIPchanged)

private:
    QString m_localIP;

public:
    explicit NetworkInfo(QObject *parent = nullptr) : QObject(parent), m_localIP("0.0.0.0")
    {
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            {
                m_localIP = address.toString();
                qDebug() << m_localIP;
                break;
            }

        }

    }

    QString localIP() const { return m_localIP; }

    //изменение из qml кода не предусматривается
    // void setMyString(const QString &value) {
    //     if (m_myString != value) {
    //         m_myString = value;
    //         emit localIPchanged();
    //     }
    // }

signals:
    void localIPchanged();

};

#endif // NETWORKINFO_H
