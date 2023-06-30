#include "alivemanager.h"
#include "helpers/logger.h"
#include "constants.h"
#include "settings.h"
#include "webapi/requestmodels/devicealiverequestmodel.h"
#include "webapi/responsemodels/devicealiveresponsemodel.h"

extern Settings settings;
extern Constants constants;


AliveManager::AliveManager(WebApiManager *webApiManager)
{
    _webApiManager = webApiManager;
    connect(&_timer, &QTimer::timeout, this, &AliveManager::On_Timeout);
}

bool AliveManager::Start()
{
    _timer.setInterval(settings.AliveTimeInterval());
    _timer.start();
    return true;
}

bool AliveManager::Stop()
{
    _timer.stop();
    return true;
}

void AliveManager::On_Timeout()
{
    QMutexLocker locker(&_timerMutex);

    DeviceAliveRequestModel deviceAliveRequest(
        constants.MobileFlexGuid(),
        constants.DeviceId(),
        constants.ApplicationId());
    deviceAliveRequest.applicationDataVersion = _applicationDataVersion;
    deviceAliveRequest.applicationVersion = _applicationVersion;

    DeviceAliveResponseModel _deviceAliveResponse;
    bool aliveOk = _webApiManager->DeviceAliveRequest(deviceAliveRequest, &_deviceAliveResponse);

    if(aliveOk){
        if(_deviceAliveResponse.IsNewApplicationDataAvailable()){
            emit NewApplicationDataAvailable();
        }
        else if(_deviceAliveResponse.IsNewApplicationDataRequeired()){
            emit NewApplicationDataRequired();
        }

        if(_deviceAliveResponse.IsNewApplicationAvailable()){
            emit NewApplicationAvailable();
        }
        else if(_deviceAliveResponse.IsNewApplicationRequeired()){
            emit NewApplicationRequired();
        }

        emit Alive();
    }

}
