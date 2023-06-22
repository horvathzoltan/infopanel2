#ifndef MASTERMODE_H
#define MASTERMODE_H

#include <QTimer>
#include "bi/tcpsocketclient.h"
#include "mode.h"
#include "webapimanager.h"


class MasterMode : public QObject ,public Mode
{
    Q_OBJECT

private:
    QTimer *_timer;
    int _counter;
    TcpSocketClient *_tcpSocketSender;
    bool _On_TimeoutGuard;

    // külső függőség
    bool IsInited(){return _webApiManager != nullptr;}
    WebApiManager *_webApiManager;
public:    
    MasterMode(WebApiManager* webApiManager, QObject* p = nullptr);
    ~MasterMode();    

    void Start();
    void On_Timeout();
};

#endif // MASTERMODE_H
