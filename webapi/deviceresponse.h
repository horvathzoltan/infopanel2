#ifndef DEVICERESPONSE_H
#define DEVICERESPONSE_H

#include "deviceresponsecodes.h"
#include "device.h"

class DeviceResponse
{
private:
    /// <summary>
    /// The result code of the webapi call for the device
    /// </summary>
    DeviceResponseCodes resultCode = DeviceResponseCodes::DeviceDoesNotExists;

    /// <summary>
    /// If the device query was successfull then the primary key of the device
    /// This can be used laster to query the device object
    /// </summary>
    Device _Device;// { get; set; } = null;
public:
    DeviceResponse();
};

#endif // DEVICERESPONSE_H
