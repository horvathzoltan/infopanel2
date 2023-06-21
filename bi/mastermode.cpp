#include "mastermode.h"

#include "helpers/logger.h"
#include "bi/cechelper.h"
#include "settings.h"
#include "webapihelper.h"

extern Settings settings;

MasterMode::MasterMode(QObject*p): QObject(p), Mode(true)
{
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
    zInfo("starting MasterMode...");

    WebApiHelper::GetDevice();

    QString cmd = QStringLiteral("master:started");       
    QString response = _tcpSocketSender->Send(cmd);
    zInfo(QStringLiteral("sent: ")+cmd+' '+(response =="ok"?"success":"failed"));

    _timer->start(5*1000);
}

void MasterMode::On_Timeout()
{
    zInfo(QStringLiteral("On_Timeout: %1").arg(_counter++));
    int pow = CECHelper::GetPowerState();
    QString cmd = QStringLiteral("pow:")+QString::number(pow);

    QString response = _tcpSocketSender->Send(cmd);
    zInfo(QStringLiteral("sent: ")+cmd+' '+(response =="ok"?"success":"failed"));
}


