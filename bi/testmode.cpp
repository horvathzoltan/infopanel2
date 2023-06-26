#include "testmode.h"
#include "bi/constants.h"
#include "helpers/logger.h"
#include "settings.h"

extern Constants constants;
extern Settings settings;

TestMode::TestMode(WebApiManager* webApiManager, QObject*p): QObject(p), Mode(true)
{
    _webApiManager = webApiManager;
}

TestMode::~TestMode()
{

}

void TestMode::Start()
{
    bool valid = IsInited();
    if(valid){
        zInfo("starting TestMode...");

        QString deviceId = constants.IsTestMode()?"dca6327492ab":constants.DeviceId();

        DeviceRequest deviceRequest(
            constants.MobileFlexGuid(),
            deviceId,
            settings.DeviceName());

        DeviceResponse deviceResponse;
        bool ok = _webApiManager->TryGetDeviceResponse(deviceRequest, &deviceResponse);
        if(ok){
            zInfo(QStringLiteral("deviceResponse: ")+QString::number(deviceResponse.resultCode));
            zInfo(QStringLiteral("deviceName: ")+deviceResponse.device.deviceName);
        }else{
            zInfo(_webApiManager->ErrorMessage());
        }
    }
}
