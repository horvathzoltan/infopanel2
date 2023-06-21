#include "bi/tcpsocketclient.h"
#include "helpers/logger.h"

#include <QElapsedTimer>
#include <QStringList>

TcpSocketClient::TcpSocketClient(const QHostAddress& host, quint16 port)
{
    _host = host;
    _port = port;
    _socket = new QTcpSocket();
}

TcpSocketClient::~TcpSocketClient()
{
    _socket->disconnectFromHost();
    _socket->waitForDisconnected(500);
    delete(_socket);
}

//https://stackoverflow.com/questions/22930118/how-to-listen-to-a-specific-port-in-qt-using-qtcpsocket

QString TcpSocketClient::Send(const QString &request)
{
    QElapsedTimer t;
    t.start();
    qint64 t1=0, t2=0, t3=0;
    QString response;

    bool connected=false, send_ok=false, receive_ok=false;
    if(_socket->state() == QAbstractSocket::SocketState::UnconnectedState){        
        _socket->connectToHost(_host, _port, QIODevice::ReadWrite);
        connected = _socket->waitForConnected(1000);
        t1 = t.elapsed();

    }
    if(connected)
    {
        QByteArray bytes_out = request.toUtf8();
        auto bytes_written = _socket->write(bytes_out);
        send_ok = bytes_written!=-1 && bytes_written==bytes_out.length();
        _socket->flush();
        t2 = t.elapsed();
        receive_ok = _socket->waitForReadyRead();
        if(receive_ok){
            QByteArray bytes_in = _socket->readAll();
            t3 = t.elapsed();
            response = QString(bytes_in);
        }
        _socket->close();
    }
    if(_verbose){
        QString a1(QStringLiteral("connect[ms]: ")+QString::number(t1)+' '+(connected?"ok":"failed"));
        QString a2(QStringLiteral("send[ms]: ")+QString::number(t2)+' '+(send_ok?"ok":"failed"));
        QString a3(QStringLiteral("receive[ms]: ")+QString::number(t3)+' '+(receive_ok?"ok":"failed"));
        zInfo(a1+'\n'+a2+'\n'+a3);
    }
    return response;
}

//void TcpSocketSender::Init()
//{

//}

