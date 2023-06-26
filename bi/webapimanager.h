#ifndef WEBAPIMANAGER_H
#define WEBAPIMANAGER_H

#include "webapi/applicationproblem.h"
#include "webapi/requestmodels/devicerequest.h"
#include "webapi/responsemodels/deviceresponse.h"

#include <QJsonDocument>
#include "helpers/httpresponse.h"

class WebApiManager
{
private:
    QString _apiLocation;
    QString GetServiceCommand(const QString& service, const QString& data);
    //ApplicationProblem _lastErr;
    QString _lastErr;
    int _lastErrCode;
public:
    WebApiManager(const QString &apiLocation);
    bool TryGetDeviceResponse(const DeviceRequest& requestModel, DeviceResponse* d);
    int LastErrCode(){return _lastErrCode;}
    QString LastErr(){return _lastErr;}
    QString ErrorMessage();

    template<typename T>
    static bool HandleResponse(const QString& str, T* d, QString *lastErr, int *lastErrCode){
        bool valid = d!=nullptr && lastErr!=nullptr && lastErrCode!=nullptr;
        bool retVal = false;
        if(valid){
            auto httpResponse = HttpResponse::Parse(str);
            bool isSuccessful = httpResponse.IsSuccessful();

            if(isSuccessful){
                auto body = httpResponse.Body().toUtf8();
                QJsonDocument jsonDocument = QJsonDocument::fromJson(body);
                bool isObject = jsonDocument.isObject();
                if(isObject){
                    QJsonObject jsonObject = jsonDocument.object();
                    *d = T::JsonParse(jsonObject);
                    retVal = true;
                }
            }
            else if(httpResponse.IsClientError()){
                if(httpResponse.IsContentType("application/problem+json")){
                    auto errors = ApplicationProblem::ErrorHandler(httpResponse.Body());
                    *lastErr = errors.join('\n');
                } else {
                    *lastErr = httpResponse.Body();// not approblem application/problem+json
                }
            }
            else{
                *lastErr = httpResponse.Body();// other error
            }
            *lastErrCode = httpResponse.StatusCode();
        }
        return retVal;
    }
};

#endif // WEBAPIMANAGER_H
