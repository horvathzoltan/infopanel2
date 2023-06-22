#include "mastermode.h"

#include "helpers/logger.h"
#include "bi/cechelper.h"
#include "settings.h"
#include "webapimanager.h"

extern Settings settings;

MasterMode::MasterMode(WebApiManager* webApiManager, QObject*p): QObject(p), Mode(true)
{
    _webApiManager = webApiManager;
    _timer = new QTimer();
    _timer->connect(_timer, &QTimer::timeout, this,  &MasterMode::On_Timeout);
    _counter = 0;    

    _tcpSocketSender = new TcpSocketClient(
        settings.SlaveHostAddress(),
        settings.SlavePort());
}

MasterMode::~MasterMode()
{
    delete(_tcpSocketSender);
    _timer->stop();
    delete(_timer);    
    zInfo("leaving MasterMode...");
}

void  MasterMode::Start()
{
    bool valid = IsInited();
    if(valid){
        zInfo("starting MasterMode...");

//        DeviceRequest deviceRequest;
//        DeviceResponse deviceResponse = _webApiManager->GetDeviceResponse(deviceRequest);

//        //zInfo(QStringLiteral("deviceResponse: ")+deviceResponse.resultCode);
//        //zInfo(QStringLiteral("deviceName: ")+deviceResponse.device.deviceName);

        QString cmd = QStringLiteral("master:started");
        QString response = _tcpSocketSender->Send(cmd);
        zInfo(QStringLiteral("sent: ")+cmd+' '+(response =="ok"?"success":"failed"));
        _On_TimeoutGuard=false;
        _timer->start(5*1000);
    }
}



void MasterMode::On_Timeout()
{    
    if(!_On_TimeoutGuard){
        _On_TimeoutGuard = true;
        zInfo(QStringLiteral("On_Timeout: %1").arg(_counter++));
        int pow = CECHelper::GetPowerState();
        QString cmd = QStringLiteral("pow:")+QString::number(pow);

        QString response = _tcpSocketSender->Send(cmd);
        zInfo(QStringLiteral("sent: ")+cmd+' '+(response =="ok"?"success":"failed"));
        _On_TimeoutGuard = false;
    }
}


