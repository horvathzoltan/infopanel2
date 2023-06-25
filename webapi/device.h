#ifndef DEVICE_H
#define DEVICE_H

#include <QJsonObject>
#include <QString>
#include "application.h"

class Device
{
public:
    /// <summary>
    /// Unique device id, unique for the device and must be the same every time (f.e. mac address of the first network card)
    /// </summary>
    QString deviceId;

    /// <summary>
    /// Device name, defined on server side (f.e. Imre's mobile phone)
    /// </summary>
    QString deviceName;//":"Teszt gép PI",

    /// <summary>
    /// Device active flag
    /// </summary>
    bool active;//":false,

    /// <summary>
    /// Informational field, contains (if exists) the last device login datetime
    /// </summary>
    QDateTime lastDeviceLoginDate;//":null,

    /// <summary>
    /// Comments
    /// </summary>
    QString comments;//":"",

    /// <summary>
    /// List of those applications, which are usable on the specified device.
    /// If defined more than once, then the client applicaiton (Android, iOS or Windows) will display a control for selecting the app tu be used
    /// See the applicaiton definition!
    /// </summary>
    QList<Application> applications;//":null}}

public:
    Device();

    static Device JsonParse(const QJsonObject& o);
};

#endif // DEVICE_H
