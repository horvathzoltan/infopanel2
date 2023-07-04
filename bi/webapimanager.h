#ifndef WEBAPIMANAGER_H
#define WEBAPIMANAGER_H

#include "settings.h"
#include "webapi/applicationproblem.h"
#include "webapi/requestmodels/devicealiverequestmodel.h"
#include "webapi/requestmodels/devicerequestmodel.h"
#include "webapi/responsemodels/devicealiveresponsemodel.h"
#include "webapi/responsemodels/deviceresponsemodel.h"
#include "webapi/requestmodels/pubapplicationdatarequestmodel.h"
#include "webapi/responsemodels/pubapplicationdataresponsemodel.h"

#include <QJsonDocument>
#include "helpers/httpresponse.h"
#include <helpers/processhelper.h>

extern Settings settings;

class WebApiManager
{
private:
    QString _apiLocation;
    QString GetServiceCommand(const QString& service, const QString& data);
    //ApplicationProblem _lastErr;
    class Error{
    public:
        QString message;
        int code;

        QString ToString();
    };
    Error _lastError;
public:
    WebApiManager(const QString &apiLocation);
    bool DeviceRequest(const DeviceRequestModel& requestModel, DeviceResponseModel* d);
    bool PubApplicationDataRequest(const PubApplicationDataRequestModel& requestModel, PubApplicationDataResponseModel* d);
    bool DeviceAliveRequest(const DeviceAliveRequestModel& requestModel, DeviceAliveResponseModel* d);


    QString LastErrorMessage(){return _lastError.ToString();}

    Application* GetApplication(DeviceResponseModel& r);

    template<typename T>
    static bool HandleResponse(const QString& str, T* d, Error *error){
        bool valid = d!=nullptr && error!=nullptr;
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
                    error->message = errors.join('\n');
                } else {
                    error->message = httpResponse.Body();// not approblem application/problem+json
                }
            }
            else{
                error->message = httpResponse.Body();// other error
            }
            error->code = httpResponse.StatusCode();
        }
        return retVal;
    }

    template<typename Resp>
    static bool Request(const QString& cmd, Resp* d, Error* error)
    {
        bool valid = d != nullptr && error!=nullptr;

        bool retVal = false;
        //QString _lastErr;
        //int _lastErrCode;

        if(valid){
            error->message.clear();
            error->code = 0;

            //QString cmd = GetServiceCommand(QStringLiteral("Device"), requestModel.ToJson());

            ProcessHelper::Output out = ProcessHelper::ShellExecute(cmd, settings.RequestTimeout()*1000);

            bool ok = out.exitCode==0;
            if(ok){
                retVal = HandleResponse<Resp>(out.stdOut, d, error);
            } else{
                error->code = out.exitCode;
                error->message = out.ToString();
            }
        } else{
            error->message=QStringLiteral("invalid call");
            error->code = -1;
        }
        return retVal;
    }
};

#endif // WEBAPIMANAGER_H
