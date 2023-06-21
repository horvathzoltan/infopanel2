#ifndef MYSERVER_H
#define MYSERVER_H

#include "processrequest.h"

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

typedef bool (*RequestProcessor)(const QString&,const QChar& sep);
typedef bool (ProcessRequest::*mRequestProcessor)(const QString&,const QChar& sep);

class TcpSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocketServer(QObject *parent = 0);
    bool Listen(const QHostAddress &address, quint16 port);

    void SetmRequestProcessor(mRequestProcessor r, ProcessRequest& pr){_mrequestProcessor = r; _pr = pr;}
    void SetVerbose(bool v ){_verbose=v;}
signals:
    
public slots:
    void newConnection();

private:
    QTcpServer *_server;
    bool _verbose = true;
    RequestProcessor _requestProcessor;
    mRequestProcessor _mrequestProcessor;
    ProcessRequest _pr;
};

#endif // MYSERVER_H

