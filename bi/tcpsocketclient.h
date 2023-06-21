#ifndef TCPSOCKETCLIENT_H
#define TCPSOCKETCLIENT_H

#include <QHostAddress>
#include <QString>
#include <QTcpSocket>

class TcpSocketClient
{
private:
    QHostAddress _host;
    quint16 _port;
    QTcpSocket *_socket;
    bool _verbose;
public:
    void SetVerbose(bool v){_verbose=v;}
    TcpSocketClient(const QHostAddress& address, quint16 port);
    ~TcpSocketClient();

    QString Send(const QString& request);
};

#endif // TCPSOCKETCLIENT_H
