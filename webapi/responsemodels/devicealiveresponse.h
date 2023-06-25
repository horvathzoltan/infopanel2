#ifndef DEVICEALIVERESPONSE_H
#define DEVICEALIVERESPONSE_H

#include "devicealiveresponsecodes.h"

class DeviceAliveResponse
{
public:
    /// <summary>
    /// Response copde -> explained at the enum
    /// </summary>
    DeviceAliveResponseCodes resultCode;// = DeviceAliveResponseCodes.Ok;

public:
    DeviceAliveResponse();
};

#endif // DEVICEALIVERESPONSE_H
