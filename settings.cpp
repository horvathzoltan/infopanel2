#include "settings.h"
#include "helpers/textfilehelper.h"
#include "helpers/inihelper.h"

#include <QStringList>

Settings::Settings()
{
    //_slaveHostAddress.setAddress("10.10.10.6");
}

bool Settings::Load(const QString &fn)
{
    bool retVal = false;
    QStringList lines;
    bool load_ok = TextFileHelper::LoadLines(fn, &lines);
    bool valid = load_ok && !lines.isEmpty();
    if(valid){
        QMap<QString, QString> m = IniHelper::Parse(lines);
        if(!m.isEmpty()){
            //Settings::Parse_masterMode(m);
            //Settings::Parse_slavePort(m);
            //Settings::Parse_slaveHostAddress(m);
            Settings::Parse_requestTimeout(m);

            Settings::Parse_slaveFullSize(m);
            // download_dir
            Settings::Parse_downloadDirectory(m);
            Settings::Parse_downloadInterval(m);
            // log_dir
            Settings::Parse_logDirectory(m);
            Settings::Parse_logTimeInterval(m);
            // counter_dir
            Settings::Parse_counterDirectory(m);
            // intervals
            Settings::Parse_aliveTimeInterval(m);
            Settings::Parse_cecTimeInterval(m);

            Settings::Parse_testMode(m);
            Settings::Parse_cecManagerVerbose(m);
            retVal = true;
        }
    }
    return retVal;
}

//bool Settings::Parse_masterMode(const QMap<QString, QString>& m){
//    bool retVal=false;
//    QString v = "";
//    bool isMode = IniHelper::TryGetValue(m, "mode", &v);
//    if(isMode && !v.isEmpty()){
//        bool parse_ok;
//        bool v_parsed = ParseMaster(v, &parse_ok);
//        if(parse_ok){
//            this->_masterMode = v_parsed;
//        }
//    }
//    return retVal;
//}

//bool Settings::ParseMaster(const QString& v, bool *ok){
//    bool master;

//    if(v==QStringLiteral("master")){
//        master=true;
//        if(ok!=nullptr) *ok=true;
//    }
//    else if(v==QStringLiteral("slave")){
//        master=false;
//        if(ok!=nullptr) *ok=true;
//    }
//    else{
//        master=false;
//        if(ok!=nullptr) *ok=false;
//    }
//    return master;
//}

bool Settings::ParseBool(const QString& v, bool *ok){
    bool value;

    if(v==QStringLiteral("true")){
        value=true;
        if(ok!=nullptr) *ok=true;
    }
    else if(v==QStringLiteral("false")){
        value=false;
        if(ok!=nullptr) *ok=true;
    }
    else{
        bool parse_ok;
        int i = v.toInt(&parse_ok);
        value=parse_ok && i!=0;
        if(ok!=nullptr) *ok=false;
    }
    return value;
}

bool Settings::Parse_slaveFullSize(const QMap<QString, QString>& m){
    bool retVal=false;
    QString v = "";
    bool isMode = IniHelper::TryGetValue(m, "slaveFullSize", &v);
    if(isMode && !v.isEmpty()){
        bool parse_ok;
        bool v_parsed = ParseBool(v, &parse_ok);
        if(parse_ok){
            this->_slaveFullSize = v_parsed;
        }
    }
    return retVal;
}


//bool Settings::Parse_slavePort(const QMap<QString, QString>& m){
//    bool retVal=false;
//    QString v = "";
//    bool isMode = IniHelper::TryGetValue(m, "slavePort", &v);
//    if(isMode && !v.isEmpty()){
//        bool parse_ok;
//        qint16 v_parsed = v.toShort(&parse_ok);
//        if(parse_ok){
//            this->_slavePort = v_parsed;
//            retVal = true;
//        }
//    }
//    return retVal;
//}

//bool Settings::Parse_slaveHostAddress(const QMap<QString, QString>& m){
//    bool retVal=false;
//    QString v = "";
//    bool isMode = IniHelper::TryGetValue(m, "slaveIp", &v);
//    if(isMode && !v.isEmpty()){
//        QHostAddress addr;
//        bool parse_ok = addr.setAddress(v);
//        if(parse_ok){
//            this->_slaveHostAddress = addr;
//            retVal = true;
//        }
//    }
//    return retVal;
//}

bool Settings::Parse_downloadDirectory(const QMap<QString, QString>& m){
    bool retVal=false;
    QString v = "";
    bool ok = IniHelper::TryGetValue(m, "downloadDirectory", &v);
    if(ok){
        this->_downloadDirectory = v;
    }
    return retVal;
}

bool Settings::Parse_aliveTimeInterval(const QMap<QString, QString> &m)
{
    bool retVal=false;
    QString v = "";
    bool isMode = IniHelper::TryGetValue(m, "aliveTimeInterval", &v);
    if(isMode && !v.isEmpty()){
        bool parse_ok;
        int v_parsed = v.toInt(&parse_ok);
        if(parse_ok && v_parsed>5 && v_parsed<3600){
            this->_aliveTimeInterval = v_parsed;
            retVal = true;
        }
    }
    return retVal;
}

bool Settings::Parse_counterDirectory(const QMap<QString, QString> &m)
{
    bool retVal=false;
    QString v = "";
    bool ok = IniHelper::TryGetValue(m, "counterDirectory", &v);
    if(ok){
        this->_counterDirectory = v;
    }
    return retVal;
}

bool Settings::Parse_logDirectory(const QMap<QString, QString> &m)
{
    bool retVal=false;
    QString v = "";
    bool ok = IniHelper::TryGetValue(m, "logDirectory", &v);
    if(ok){
        this->_logDirectory = v;
    }
    return retVal;
}

bool Settings::Parse_downloadInterval(const QMap<QString, QString> &m)
{
    bool retVal=false;
    QString v = "";
    bool isMode = IniHelper::TryGetValue(m, "downloadInterval", &v);
    if(isMode && !v.isEmpty()){
        bool parse_ok;
        int v_parsed = v.toInt(&parse_ok);
        if(parse_ok && v_parsed>5 && v_parsed<3600){
            this->_aliveTimeInterval = v_parsed;
            retVal = true;
        }
    }
    return retVal;
}


bool Settings::Parse_logTimeInterval(const QMap<QString, QString> &m)
{
    bool retVal=false;
    QString v = "";
    bool isMode = IniHelper::TryGetValue(m, "logTimeInterval", &v);
    if(isMode && !v.isEmpty()){
        bool parse_ok;
        int v_parsed = v.toInt(&parse_ok);
        if(parse_ok && v_parsed>5 && v_parsed<3600){
            this->_logTimeInterval = v_parsed;
            retVal = true;
        }
    }
    return retVal;
}

bool Settings::Parse_cecTimeInterval(const QMap<QString, QString> &m)
{
    bool retVal=false;
    QString v = "";
    bool isMode = IniHelper::TryGetValue(m, "cecTimeInterval", &v);
    if(isMode && !v.isEmpty()){
        bool parse_ok;
        int v_parsed = v.toInt(&parse_ok);
        if(parse_ok && v_parsed>5 && v_parsed<3600){
            this->_cecTimeInterval = v_parsed;
            retVal = true;
        }
    }
    return retVal;
}

bool Settings::Parse_requestTimeout(const QMap<QString, QString> &m)
{
    bool retVal=false;
    QString v = "";
    bool isMode = IniHelper::TryGetValue(m, "requestTimeout", &v);
    if(isMode && !v.isEmpty()){
        bool parse_ok;
        int v_parsed = v.toInt(&parse_ok);
        if(parse_ok && v_parsed>1 && v_parsed<300){
            this->_requestTimeout = v_parsed;
            retVal = true;
        }
    }
    return retVal;
}

bool Settings::Parse_testMode(const QMap<QString, QString>& m){
    bool retVal=false;
    QString v = "";
    bool isMode = IniHelper::TryGetValue(m, "testMode", &v);
    if(isMode && !v.isEmpty()){
        bool parse_ok;
        bool v_parsed = ParseBool(v, &parse_ok);
        if(parse_ok){
            this->_testMode = v_parsed;
        }
    }
    return retVal;
}

bool Settings::Parse_cecManagerVerbose(const QMap<QString, QString> &m)
{
    bool retVal=false;
    QString v = "";
    bool isMode = IniHelper::TryGetValue(m, "cecManagerVerbose", &v);
    if(isMode && !v.isEmpty()){
        bool parse_ok;
        bool v_parsed = ParseBool(v, &parse_ok);
        if(parse_ok){
            this->_cecManagerVerbose = v_parsed;
        }
    }
    return retVal;
}


