#ifndef DEVICEALIVERESPONSE_H
#define DEVICEALIVERESPONSE_H

#include "webapi/enums/devicealiveresponsecodes.h"

#include <QJsonObject>

class DeviceAliveResponse
{
public:
    /// <summary>
    /// Response copde -> explained at the enum
    /// </summary>
    DeviceAliveResponseCodes resultCode;// = DeviceAliveResponseCodes.Ok;

public:
    DeviceAliveResponse();

    static DeviceAliveResponse JsonParse(const QJsonObject& o);
};

#endif // DEVICEALIVERESPONSE_H
