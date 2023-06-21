#ifndef TCPSOCKETSENDER_H
#define TCPSOCKETSENDER_H

#include <QHostAddress>
#include <QString>
#include <QTcpSocket>

class TcpSocketSender
{
private:
    QHostAddress _host;
    quint16 _port;
    QTcpSocket *_socket;
    bool _verbose;
public:
    void SetVerbose(bool v){_verbose=v;}
    TcpSocketSender(const QHostAddress& address, quint16 port);
    ~TcpSocketSender();

    QString Send(const QString& request);
};

#endif // TCPSOCKETSENDER_H
