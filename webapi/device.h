#ifndef DEVICE_H
#define DEVICE_H

#include <QJsonObject>
#include <QString>

class Device
{
public:
    /// <summary>
    /// Unique device id, unique for the device and must be the same every time (f.e. mac address of the first network card)
    /// </summary>
    QString deviceId;

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
