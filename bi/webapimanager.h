#ifndef WEBAPIMANAGER_H
#define WEBAPIMANAGER_H

#include "webapi/devicerequest.h"
#include <webapi/deviceresponse.h>

class WebApiManager
{
private:
    QString _apiLocation;
    QString GetServiceUrl(const QString& service, const QString& data);
public:
    WebApiManager(const QString &apiLocation);
    DeviceResponse GetDeviceResponse(const DeviceRequest& r);
};

#endif // WEBAPIMANAGER_H
