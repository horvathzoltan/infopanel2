#ifndef DEVICERESPONSE_H
#define DEVICERESPONSE_H

#include "deviceresponsecodes.h"
#include "device.h"

class DeviceResponse
{
public:
    /// <summary>
    /// The result code of the webapi call for the device
    /// </summary>
    DeviceResponseCodes resultCode = DeviceResponseCodes::DeviceDoesNotExists;

    /// <summary>
    /// If the device query was successfull then the primary key of the device
    /// This can be used laster to query the device object
    /// </summary>
    Device device;// { get; set; } = null;
public:
    DeviceResponse();

    static DeviceResponse JsonParse(const QJsonObject& o);
};

#endif // DEVICERESPONSE_H
