#ifndef SETTINGS_H
#define SETTINGS_H


#include <QHostAddress>
#include <QString>

class Settings{
private:
    //bool _masterMode=true;
    //QHostAddress _slaveHostAddress;
    //qint16 _slavePort=8081;
    bool _slaveFullSize = false;
    bool _testMode = false;
    QString _apiLocation = QStringLiteral("https://api.mobileflex.hu");
    QString _deviceName = QStringLiteral("deviceName");
    QString _downloadDirectory = QStringLiteral("/home/zoli/pubImageItems");
    QString _counterDirectory = QStringLiteral("/home/zoli/pubImageItemCounters");
    QString _logDirectory = QStringLiteral("/home/zoli/pubImageItemLogs");
    int _aliveTimeInterval = 60;//sec //1000*60*5 = 5 min
    int _logTimeInterval = 120;//sec//1000*60*5 = 5 min
    int _cecTimeInterval = 10;//sec // 1000*60*5 = 5 min
    int _downloadInterval = 60;//sec
    int _requestTimeout = 4;//sec
    bool _cecManagerVerbose = false;

    //static bool ParseMaster(const QString& v, bool *ok);
    static bool ParseBool(const QString& v, bool *ok);

    //bool Parse_masterMode(const QMap<QString, QString>& m);
    //bool Parse_slavePort(const QMap<QString, QString>& m);
    //bool Parse_slaveHostAddress(const QMap<QString, QString>& m);
    bool Parse_requestTimeout(const QMap<QString, QString>& m);

    bool Parse_slaveFullSize(const QMap<QString, QString>& m);
    // download_dir
    bool Parse_downloadDirectory(const QMap<QString, QString>& m);
    bool Parse_downloadInterval(const QMap<QString, QString>& m);
    // log_dir
    bool Parse_logDirectory(const QMap<QString, QString>& m);
    bool Parse_logTimeInterval(const QMap<QString, QString>& m);
    // counter_dir
    bool Parse_counterDirectory(const QMap<QString, QString>& m);
    // intervals
    bool Parse_aliveTimeInterval(const QMap<QString, QString>& m);                
    bool Parse_cecTimeInterval(const QMap<QString, QString>& m);

    bool Parse_testMode(const QMap<QString, QString>& m);
    bool Parse_cecManagerVerbose(const QMap<QString, QString>& m);
public:
    Settings();
    bool Load(const QString& fn);
    //QHostAddress SlaveHostAddress(){return _slaveHostAddress;}
    //qint16 SlavePort(){return _slavePort;}
    //bool MasterMode(){return _masterMode;}
    bool SlaveFullSize(){return _slaveFullSize;}
    QString ApiLocation(){return _apiLocation;}
    QString DeviceName(){return _deviceName;}
    QString DownloadDirectory(){return _downloadDirectory;}
    int DownloadInterval(){return _downloadInterval;}
    QString CounterDirectory(){return _counterDirectory;}
    QString LogDirectory(){return _logDirectory;}
    int AliveTimeInterval(){return _aliveTimeInterval;}
    int LogTimeInterval(){return _logTimeInterval;}
    int CecTimeInterval(){return _cecTimeInterval;}
    int RequestTimeout(){return _requestTimeout;}
    bool TestMode(){return _testMode;}
    bool CecManagerVerbose(){return _cecManagerVerbose;}
};

#endif // SETTINGS_H
