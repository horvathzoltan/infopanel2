#ifndef SETTINGS_H
#define SETTINGS_H


#include <QHostAddress>
#include <QString>

class Settings{
private:
    bool _masterMode=true;
    QHostAddress _slaveHostAddress;
    qint16 _slavePort=8081;
    bool _slaveFullSize = false;
    QString _apiLocation = QStringLiteral("https://api.mobileflex.hu");
    QString _deviceName = QStringLiteral("deviceName");
    QString _downloadDirectory = QStringLiteral("/home/zoli/pubImageItems");

    static bool ParseMaster(const QString& v, bool *ok);
    static bool ParseBool(const QString& v, bool *ok);

    bool Parse_masterMode(const QMap<QString, QString>& m);
    bool Parse_slaveFullSize(const QMap<QString, QString>& m);
    bool Parse_slavePort(const QMap<QString, QString>& m);
    bool Parse_slaveHostAddress(const QMap<QString, QString>& m);
    bool Parse_downloadDirectory(const QMap<QString, QString>& m);

public:
    Settings();
    bool Load(const QString& fn);
    QHostAddress SlaveHostAddress(){return _slaveHostAddress;}
    qint16 SlavePort(){return _slavePort;}
    bool MasterMode(){return _masterMode;}
    bool SlaveFullSize(){return _slaveFullSize;}
    QString ApiLocation(){return _apiLocation;}
    QString DeviceName(){return _deviceName;}
    QString DownloadDirectory(){return _downloadDirectory;}
};

#endif // SETTINGS_H
