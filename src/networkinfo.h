#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QNetworkInterface>

class NetworkInfo : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString localIP READ localIP NOTIFY localIPchanged)
    Q_PROPERTY(QString deviceIP READ deviceIP NOTIFY deviceIPchanged)

private:
    QString m_localIP;
    QString m_deviceIP;

public:
    explicit NetworkInfo(QObject *parent = nullptr) : QObject(parent), m_localIP("0.0.0.0"), m_deviceIP("0.0.0.00")
    {
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost); //сразу просто получить и записать адреса
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            {
                if(m_localIP == "0.0.0.0"){
                    m_localIP = address.toString();
                    qDebug() << m_localIP;
                }
                else{
                    m_deviceIP = address.toString();
                    qDebug() << m_deviceIP;
                }

            }
        }

    }

    QString localIP() const { return m_localIP; }
    QString deviceIP() const { return m_deviceIP; }

    //изменение из qml кода не предусматривается
    // void setMyString(const QString &value) {
    //     if (m_myString != value) {
    //         m_myString = value;
    //         emit localIPchanged();
    //     }
    // }

signals:
    void localIPchanged();
    void deviceIPchanged();

};

#endif // NETWORKINFO_H
