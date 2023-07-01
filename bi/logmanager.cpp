#include "logmanager.h"

#include "constants.h"
#include "settings.h"
#include "webapi/requestmodels/publogrequestmodel.h"
#include "helpers/textfilehelper.h"

#include <QDir>

extern Settings settings;
extern Constants constants;

LogManager::LogManager()
{

}

bool LogManager::Start()
{
    bool valid = !_timer.isActive();
    bool retVal = false;
    if(valid){
        _timer.setInterval(settings.LogTimeInterval());
        _timer.start();
        retVal = true;
    }
    return retVal;
}

bool LogManager::Stop()
{
    bool valid = _timer.isActive();
    bool retVal = false;
    if(valid){
        _timer.stop();
        retVal = true;
    }
    return retVal;
}

void LogManager::On_Timeout()
{
    QMutexLocker locker(&_timerMutex);
    QDir downloadDir(settings.LogDirectory());
    auto filenamelist = downloadDir.entryList({"*.log"},QDir::Files);
    bool valid = !filenamelist.isEmpty();
    //https://api.mobileflex.hu/LogUpload/Pub
    if(valid){
        for(auto&a:filenamelist){
            PubLogRequestModel pubLogRequestModel(
                constants.MobileFlexGuid(),
                constants.DeviceId(),
                constants.ApplicationId());

            QString content;
            TextFileHelper::Load(a, &content);
            pubLogRequestModel.logItems = LogUploadModel::ParseList(content);
        }
    }
    return;
}
