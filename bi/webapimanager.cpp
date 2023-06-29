#include "bi/constants.h"
#include "helpers/logger.h"

#include "webapimanager.h"
#include "helpers/processhelper.h"
#include "webapi/requestmodels/devicerequestmodel.h"
#include "webapi/applicationproblem.h"
#include <QJsonDocument>
#include "helpers/httpresponse.h"

extern Constants constants;

WebApiManager::WebApiManager(const QString &apiLocation)
{
    _apiLocation = apiLocation;
}

/*
curl --location 'https://api.mobileflex.hu/Device' \
--header 'Content-Type: application/json' \
--data '{
    "id": "7a0e0865-08b2-488a-8a20-c327ce28e59d",
    "deviceId": "macaddress",
    "deviceName": "Teszt gép PI"
}'


{"resultCode":101,
"device":{
"deviceId":"macaddress",
"deviceName":"Teszt gép PI",
"active":false,
"lastDeviceLoginDate":null,
"comments":"",
"applications":null}}

ERROR:
{
  "type": "https://tools.ietf.org/html/rfc7231#section-6.5.1",
  "title": "One or more validation errors occurred.",
  "status": 400,
  "traceId": "00-d6eacd6cee8a6f131f5db2fb586de5ee-d82f3f34514497ae-00",
  "errors": {
    "deviceRequest": [
      "The deviceRequest field is required."
    ],
    "$.id": [
      "The JSON value could not be converted to System.Guid. Path: $.id | LineNumber: 1 | BytePositionInLine: 49."
    ]
  }
}
*/
/// {"resultCode":101,"device":{"deviceId":"macaddress","deviceName":"Teszt gép PI","active":false,"lastDeviceLoginDate":null,"comments":"","applications":null}}
/// https://thecodeprogram.com/how-to-use-json-data-with-qt-c--

//https://curl.se/docs/manpage.html#--stderr
// curl -i


/*
Response      = Status-Line               ; Section 6.1
                       *(( general-header        ; Section 4.5
                        | response-header        ; Section 6.2
                        | entity-header ) CRLF)  ; Section 7.1
                       CRLF
                       [ message-body ]          ; Section 7.2


Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
*/

QString WebApiManager::Error::ToString()
{
    static const QString msg = QStringLiteral("error(%1): %2");
    return msg.arg(code).arg(message);
}

QString WebApiManager::GetServiceCommand(const QString& service, const QString& data)
{
    static const QString CMD = QStringLiteral(R"(curl -i --location '%1/%2' --header 'Content-Type: application/json' --data '%3')");
    return CMD.arg(_apiLocation,service,data);
}

const Application* WebApiManager::GetApplication(const DeviceResponseModel& r)
{
    return r.GetApplication(constants.ApplicationId());
}
//https://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html
//https://www.ietf.org/rfc/rfc2616.txt

//bool WebApiManager::DeviceRequest(const DeviceRequestModel& requestModel, DeviceResponseModel* d)
//{
//    bool retVal = false;
//    bool valid = d!=nullptr;
//    if(valid){
//        _lastErr.clear();
//        _lastErrCode = 0;

//        QString cmd = GetServiceCommand(QStringLiteral("Device"), requestModel.ToJson());

//        ProcessHelper::Output out = ProcessHelper::ShellExecute(cmd);

//        bool ok = out.exitCode==0;
//        if(ok){
//            retVal = HandleResponse<DeviceResponseModel>(out.stdOut, d, &_lastErr, &_lastErrCode);
//        } else{
//            _lastErrCode = out.exitCode;
//            _lastErr = out.ToString();
//        }
//    } else{
//        _lastErr=QStringLiteral("invalid call");
//        _lastErrCode = -1;
//    }
//    return retVal;
//}

bool WebApiManager::DeviceRequest(const DeviceRequestModel& requestModel,
                                  DeviceResponseModel* responseModel){
    bool retVal = false;
    QString cmd = GetServiceCommand(QStringLiteral("Device"), requestModel.ToJson());

    bool ok = Request(cmd,responseModel,&_lastError);
    if(ok){
        retVal = true;
    }
    return retVal;
}

bool WebApiManager::PubApplicationDataRequest(const PubApplicationDataRequestModel &requestModel,
                                              PubApplicationDataResponseModel *responseModel)
{
    bool retVal = false;
    QString cmd = GetServiceCommand(QStringLiteral("ApplicationData/Pub"), requestModel.ToJson());

    bool ok = Request(cmd,responseModel,&_lastError);
    if(ok){
        retVal = true;
    }
    return retVal;
}

bool WebApiManager::DeviceAliveRequest(const DeviceAliveRequestModel &requestModel,
                                       DeviceAliveResponseModel *responseModel)
{
    bool retVal = false;
    QString cmd = GetServiceCommand(QStringLiteral("DeviceAlive"), requestModel.ToJson());

    bool ok = Request(cmd,responseModel,&_lastError);
    if(ok){
        retVal = true;
    }
    return retVal;
}



