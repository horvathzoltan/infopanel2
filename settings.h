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
    QString _counterDirectory = QStringLiteral("/home/zoli/pubImageItemCounters");
    QString _logDirectory = QStringLiteral("/home/zoli/pubImageItemLogs");
    int _aliveTimeInterval = 1000*2;//5 sec //1000*60*5; // 5 min
    int _logTimeInterval = 1000*7;//5 sec //1000*60*5; // 5 min
    int _downloadInterval = 3;

    static bool ParseMaster(const QString& v, bool *ok);
    static bool ParseBool(const QString& v, bool *ok);

    bool Parse_masterMode(const QMap<QString, QString>& m);
    bool Parse_slaveFullSize(const QMap<QString, QString>& m);
    bool Parse_slavePort(const QMap<QString, QString>& m);
    bool Parse_slaveHostAddress(const QMap<QString, QString>& m);
    bool Parse_downloadDirectory(const QMap<QString, QString>& m);
    bool Parse_aliveTimeInterval(const QMap<QString, QString>& m);
    bool Parse_counterDirectory(const QMap<QString, QString>& m);
    bool Parse_downloadInterval(const QMap<QString, QString>& m);
    bool Parse_logDirectory(const QMap<QString, QString>& m);
    bool Parse_logTimeInterval(const QMap<QString, QString>& m);

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
    int DownloadInterval(){return _downloadInterval;}
    QString CounterDirectory(){return _counterDirectory;}
    QString LogDirectory(){return _logDirectory;}
    int AliveTimeInterval(){return _aliveTimeInterval;}
    int LogTimeInterval(){return _logTimeInterval;}
};

#endif // SETTINGS_H
