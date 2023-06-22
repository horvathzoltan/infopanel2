#ifndef DEVICE_H
#define DEVICE_H

#include <QJsonObject>
#include <QString>

class Device
{
public:
    QString deviceId;//":"macaddress",
    QString deviceName;//":"Teszt gép PI",
    bool active;//":false,
    QDateTime lastDeviceLoginDate;//":null,
    QString comments;//":"",
    QString applications;//":null}}
public:
    Device();

    static Device JsonParse(const QJsonObject& o);
};

#endif // DEVICE_H
