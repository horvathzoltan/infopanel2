#ifndef SLAVEMODE_H
#define SLAVEMODE_H

#include <QObject>
#include "form3.h"
#include "frame2.h"
#include "mode.h"
#include "processrequest.h"
#include "tcpsocketserver.h"

class SlaveMode : public QObject, public Mode
{
    Q_OBJECT

private:
    Form3* _w1 = nullptr;
    Frame2* _w2 = nullptr;
    ProcessRequest _processRequest;
    TcpSocketServer _tcpSocketServer;
public:
    SlaveMode(QObject* p = nullptr);
    ~SlaveMode();

    void Init();
};

#endif // SLAVEMODE_H
