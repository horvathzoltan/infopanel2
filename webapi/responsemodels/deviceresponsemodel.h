#ifndef DEVICERESPONSEMODEL_H
#define DEVICERESPONSEMODEL_H

#include "webapi/device.h"

class DeviceResponseModel
{
public:
    enum Codes:int{
        SpecifyGlobalUrl = -99,
        Undefined = -1,
        Ok = 0,
        InvalidRequestGuid,
        SqlError,
        DataServiceInstanceDoesNotExist,
        DeviceDoesNotExists = 100,
        DeviceInactive,
        DeviceAccessDenied
    };

    /// <summary>
    /// The result code of the webapi call for the device
    /// </summary>
    Codes resultCode = Codes::DeviceDoesNotExists;

    /// <summary>
    /// If the device query was successfull then the primary key of the device
    /// This can be used laster to query the device object
    /// </summary>
    Device device;

public:
    DeviceResponseModel();
    static DeviceResponseModel JsonParse(const QJsonObject& o);
    const Application* GetApplication(QUuid appid) const;
};

#endif // DEVICERESPONSEMODEL_H
