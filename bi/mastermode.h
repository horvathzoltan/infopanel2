#ifndef MASTERMODE_H
#define MASTERMODE_H

#include <QTimer>
#include "bi/tcpsocketsender.h"
#include "mode.h"


class MasterMode : public QObject ,public Mode
{
    Q_OBJECT

private:
    QTimer *_timer;
    int _counter;
    TcpSocketSender *_tcpSocketSender;

public:
    MasterMode(QObject* p = nullptr);
    ~MasterMode();

    void Start();
    void On_Timeout();

};

#endif // MASTERMODE_H
