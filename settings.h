#ifndef SETTINGS_H
#define SETTINGS_H


#include <QHostAddress>
#include <QString>

class Settings{
private:
    bool _masterMode=true;
    QHostAddress _slaveHostAddress;
    qint16 _slavePort=8081;

    static bool ParseMaster(const QString& v, bool *ok);
    bool Parse_masterMode(const QMap<QString, QString>& m);
    bool Parse_slavePort(const QMap<QString, QString>& m);
    bool Parse_slaveHostAddress(const QMap<QString, QString>& m);

public:
    Settings();
    bool Load(const QString& fn);
    QHostAddress SlaveHostAddress(){return _slaveHostAddress;}
    qint16 SlavePort(){return _slavePort;}
    bool MasterMode(){return _masterMode;}
};

#endif // SETTINGS_H
