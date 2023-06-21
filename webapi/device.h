#ifndef DEVICE_H
#define DEVICE_H

#include <QString>

class Device
{
private:
    QString deviceId;//":"macaddress",
    QString deviceName;//":"Teszt gép PI",
    QString active;//":false,
    QString lastDeviceLoginDate;//":null,
    QString comments;//":"",
    QString applications;//":null}}
public:
    Device();
};

#endif // DEVICE_H
