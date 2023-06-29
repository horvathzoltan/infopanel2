#ifndef MASTERMODE_H
#define MASTERMODE_H

#include <QMutex>
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
    QMutex _timerMutex;

    // külső függőség
    bool IsInited(){return _webApiManager != nullptr;}
    WebApiManager *_webApiManager;
public:    
    MasterMode(WebApiManager* webApiManager, QObject* p = nullptr);
    ~MasterMode();

    bool Start();
    void On_Timeout();
};

#endif // MASTERMODE_H
