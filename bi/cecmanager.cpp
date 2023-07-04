#include "cecmanager.h"

#include "constants.h"
#include "settings.h"

#include "bi/cechelper.h"

extern Settings settings;
extern Constants constants;

CecManager::CecManager()
{
    connect(&_timer, &QTimer::timeout, this, &CecManager::On_Timeout);
}

bool CecManager::Start()
{
    bool valid = !_timer.isActive();
    bool retVal = false;
    if(valid){
        _timer.setInterval(settings.CecTimeInterval()*1000);
        _timer.start();
        retVal = true;
    }
    return retVal;
}

bool CecManager::Stop()
{
    bool valid = _timer.isActive();
    bool retVal = false;
    if(valid){
        _timer.stop();
        retVal = true;
    }
    return retVal;
}

void CecManager::On_Timeout()
{
    QMutexLocker locker(&_timerMutex);

    int pow = CECHelper::GetPowerState(0);    
    CECHelper::SetPowerState(1, pow);

    return;
}
