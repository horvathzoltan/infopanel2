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
    //ApplicationProblem _lastErr;
    QString _lastErr;
    int _lastErrCode;
public:
    WebApiManager(const QString &apiLocation);
    bool TryGetDeviceResponse(const DeviceRequest& requestModel, DeviceResponse* d);
    int LastErrCode(){return _lastErrCode;}
    QString LastErr(){return _lastErr;}
    QString ErrorMessage();
};

#endif // WEBAPIMANAGER_H
