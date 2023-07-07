#include "cecmanager.h"
#include "constants.h"
#include "helpers/logger.h"
#include "settings.h"
#include "bi/cechelper.h"
#include <QApplication>

extern Settings settings;
extern Constants constants;

CecManager::CecManager()
{
    _timerThread = new QThread();
    QObject::connect(_timerThread, &QThread::started, [=]()
                     {
                         _timer = new QTimer(_timerThread);
                         _timer->setInterval(settings.CecTimeInterval()*1000);
                         _timer->setSingleShot(true);
                         QObject::connect(_timer, &QTimer::timeout,[=]()
                          {
                            if(_enabled) On_Timeout();
                            _timer->start();
                         });
                         _timer->start();
                     });
    _timerThread->start();
}

CecManager::~CecManager()
{
    _timerThread->quit();
    _timerThread->wait();
    _timerThread->deleteLater();
}

void CecManager::On_Timeout()
{
   // if(!_On_TimeoutGuard){ // ha egymásra fut, eldobjuk
   //     _On_TimeoutGuard=true;
        int pow0 = CECHelper::GetPowerState(0);

        if(pow0==1){
            if(_verbose) zInfo("CEC ON");
            CECHelper::SetPowerState(1, 1);
            emit PowerOn();
        }
        else if(pow0==0){
            if(_verbose) zInfo("CEC OFF");
            CECHelper::SetPowerState(1, 0);
            emit PowerOff();
        } else{
            if(_verbose) zInfo("CEC unknown_state");
        }

   //     _On_TimeoutGuard=false;
    //}
    return;
}

