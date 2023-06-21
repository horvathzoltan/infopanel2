#include "bi/tcpsocketserver.h"
#include "helpers/logger.h"

#include <QElapsedTimer>

TcpSocketServer::TcpSocketServer(QObject *parent) :
    QObject(parent)
{
    _server = new QTcpServer(this);

    connect(_server, SIGNAL(newConnection()), this, SLOT(newConnection()));   
}

bool TcpSocketServer::Listen(const QHostAddress &address, quint16 port){
    bool started = _server->listen(address, port);

    if(_verbose){
        zInfo((started)?"Server started!":"Server could not start!");
    }
    return started;
}

void TcpSocketServer::newConnection()
{
    QElapsedTimer t;
    t.start();
    qint64 t1=0, t2=0, t3=0;
    QString request;
    bool connected=false, receive_ok=false, send_ok = false;
    const QByteArray bytes_out = QStringLiteral("ok").toUtf8();

    QTcpSocket *socket = _server->nextPendingConnection();
    connected = socket!=nullptr;


    if(connected)
    {
        receive_ok = socket->waitForReadyRead(1000);
        t1 = t.elapsed();
        if(receive_ok){
            QByteArray bytes_in = socket->readAll();
            t2 = t.elapsed();
            auto bytes_written = socket->write(bytes_out);
            send_ok = bytes_written!=-1 && bytes_written==bytes_out.length();
            socket->flush();
            t3 = t.elapsed();
            request = QString(bytes_in);
        }
        socket->close();
    }

    if(_verbose){
        QString a1(QStringLiteral("connect[ms]: ")+QString::number(t1)+' '+(connected?"ok":"failed"));
        QString a2(QStringLiteral("receive[ms]: ")+QString::number(t2)+' '+(receive_ok?"ok":"failed"));
        QString a3(QStringLiteral("send[ms]: ")+QString::number(t3)+' '+(send_ok?"ok":"failed"));

        zInfo(a1+'\n'+a2+'\n'+a3);
    }


    if(_mrequestProcessor != nullptr){
        (_pr.*_mrequestProcessor)(request, ':');
    }
}


