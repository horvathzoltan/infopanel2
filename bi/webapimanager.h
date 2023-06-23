#ifndef WEBAPIMANAGER_H
#define WEBAPIMANAGER_H

#include "webapi/applicationproblem.h"
#include "webapi/devicerequest.h"
#include <webapi/deviceresponse.h>

class WebApiManager
{
private:
    QString _apiLocation;
    QString GetServiceUrl(const QString& service, const QString& data);
    ApplicationProblem _lastErr;
public:
    WebApiManager(const QString &apiLocation);
    bool TryGetDeviceResponse(const DeviceRequest& requestModel, DeviceResponse* d);
};

#endif // WEBAPIMANAGER_H
