#ifndef DEVICEALIVERESPONSEMODEL_H
#define DEVICEALIVERESPONSEMODEL_H

#include <QJsonObject>

class DeviceAliveResponseModel
{
public:
    enum Codes:int
    {
        Ok = 0x00,
        InvalidRequestGuid = 0x01,
        SqlError = 0x02,
        DeviceError = 0x04,
        NewApplicationVersionAvailable = 0x10,
        NewApplicationVersionRequired = 0x20,
        NewApplicationDataAvailable = 0x40,
        NewApplicationDataRequired = 0x80,
    };

    /// <summary>
    /// Response copde -> explained at the enum
    /// </summary>
    Codes resultCode = Codes::Ok;

public:
    DeviceAliveResponseModel();

    static DeviceAliveResponseModel JsonParse(const QJsonObject& o);
};

#endif // DEVICEALIVERESPONSEMODEL_H
