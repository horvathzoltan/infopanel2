#include "webapihelper.h"
#include "helpers/logger.h"
#include "helpers/processhelper.h"

/*
curl --location 'https://api.mobileflex.hu/Device' \
--header 'Content-Type: application/json' \
--data '{
    "id": "7a0e0865-08b2-488a-8a20-c327ce28e59d",
    "deviceId": "macaddress",
    "deviceName": "Teszt gép PI"
}'
*/
/*
 * {"resultCode":101,
 * "device":{
 * "deviceId":"macaddress",
 * "deviceName":"Teszt gép PI",
 * "active":false,
 * "lastDeviceLoginDate":null,
 * "comments":"",
 * "applications":null}}
*/
/// "{"resultCode":101,"device":{"deviceId":"macaddress","deviceName":"Teszt gép PI","active":false,"lastDeviceLoginDate":null,"comments":"","applications":null}}"
/// https://thecodeprogram.com/how-to-use-json-data-with-qt-c--
void WebApiHelper::GetDevice()
{
    const QString CMD = QStringLiteral(R"(curl --location 'https://api.mobileflex.hu/Device' --header 'Content-Type: application/json' --data '
{
    "id": "7a0e0865-08b2-488a-8a20-c327ce28e59d",
    "deviceId": "macaddress",
    "deviceName": "Teszt gép PI"
}')");
    auto o = ProcessHelper::ShellExecute(CMD);
    bool ok = o.stdErr.isEmpty() && o.exitCode==0;
    if(ok){
        zInfo("response:"+o.stdOut);
    }
}
