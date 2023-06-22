#include "webapimanager.h"
//#include "helpers/logger.h"
#include "helpers/processhelper.h"
#include "webapi/devicerequest.h"

#include <QJsonDocument>


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
//https://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html
//https://www.ietf.org/rfc/rfc2616.txt

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
    static const QString CMD = QStringLiteral(R"(curl --location '%1/%2' --header 'Content-Type: application/json' --data '%3')");
    return CMD.arg(_apiLocation).arg(service).arg(data);
}

DeviceResponse WebApiManager::GetDeviceResponse(const DeviceRequest& requestModel)
{
    QString CMD = GetServiceUrl(QStringLiteral("Device"), requestModel.ToJson());

    DeviceResponse responseModel;

    ProcessHelper::Output out = ProcessHelper::ShellExecute(CMD);
    bool ok = out.stdErr.isEmpty() && out.exitCode==0;
    if(ok){
        QJsonDocument jsonDocument = QJsonDocument::fromJson(out.stdOut.toUtf8());
        if(jsonDocument.isObject()){
            QJsonObject jsonObject = jsonDocument.object();
            responseModel = DeviceResponse::JsonParse(jsonObject);
        }
    }

    return responseModel;
}
