#include "helpers/logger.h"

#include "webapimanager.h"
#include "helpers/processhelper.h"
#include "webapi/devicerequest.h"
#include "webapi/applicationproblem.h"
#include <QJsonDocument>
#include "helpers/httpresponse.h"

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
*/
/// "{"resultCode":101,"device":{"deviceId":"macaddress","deviceName":"Teszt gép PI","active":false,"lastDeviceLoginDate":null,"comments":"","applications":null}}"
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
QString WebApiManager::GetServiceUrl(const QString& service, const QString& data)
{
    static const QString CMD = QStringLiteral(R"(curl -i --location '%1/%2' --header 'Content-Type: application/json' --data '%3')");
    return CMD.arg(_apiLocation).arg(service).arg(data);
}

//https://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html
//https://www.ietf.org/rfc/rfc2616.txt
//HTTPResponse

bool WebApiManager::TryGetDeviceResponse(const DeviceRequest& requestModel, DeviceResponse* d)
{
    bool retVal = false;
    bool valid = d!=nullptr;

    QString url = GetServiceUrl(QStringLiteral("Device"), requestModel.ToJson());


    ProcessHelper::Output out = ProcessHelper::ShellExecute(url);

    bool ok = out.exitCode==0;
    if(ok){
        auto httpResponse = HttpResponse::Parse(out.stdOut);

        if(httpResponse.IsSuccessful()){
            QJsonDocument jsonDocument = QJsonDocument::fromJson(httpResponse.Body().toUtf8());
            if(jsonDocument.isObject()){
                QJsonObject jsonObject = jsonDocument.object();
                *d = DeviceResponse::JsonParse(jsonObject);
            }
        }
        else if(httpResponse.IsClientError()){
            if(httpResponse.IsContentType("application/problem+json")){
                QJsonDocument jsonDocument = QJsonDocument::fromJson(out.stdOut.toUtf8());
                if(jsonDocument.isObject()){
                    QJsonObject jsonObject = jsonDocument.object();
                    _lastErr = ApplicationProblem::JsonParse(jsonObject);
                }
                else{
                    _lastErr =  ApplicationProblem();//notjson
                }
            } else{
                _lastErr =  ApplicationProblem();// not approblem application/problem+json
            }
        }
        else{
            _lastErr = ApplicationProblem();// other error
        }
    }

    return retVal;
}
