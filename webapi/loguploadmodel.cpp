#include "loguploadmodel.h"
#include "helpers/nameof.h"

#include <QJsonObject>
#include <QJsonDocument>

LogUploadModel::LogUploadModel()
{

}

QString LogUploadModel::ToJson() const
{
    QJsonObject o;

    static const QString nameof_id = nameof(id);
    static const QString nameof_displayTimeStamp = nameof(displayTimeStamp);
    static const QString nameof_seconds = nameof(seconds);

    o.insert(nameof_id, id.toString(QUuid::WithoutBraces));
    o.insert(nameof_displayTimeStamp, displayTimeStamp.toString(Qt::DateFormat::ISODateWithMs));
    o.insert(nameof_seconds, QString::number(seconds));

    QJsonDocument jsonDoc;
    jsonDoc.setObject(o);
    QString str = jsonDoc.toJson();

    return str;
}

LogUploadModel LogUploadModel::Parse(const QString &txt)
{
    LogUploadModel e;
    bool valid = !txt.isEmpty();
    if(valid){
        QStringList tokens = txt.split(';');
        bool valid2 = tokens.length()>=3;
        if(valid2){
            bool ok;
            QUuid v0 =  QUuid::fromString(tokens[0]);
            if(v0.isNull()){
                e.id = v0;
            }
            QDateTime v1 = QDateTime::fromString(tokens[1], Qt::DateFormat::ISODateWithMs);
            if(v1.isValid()){
                e.displayTimeStamp=v1;
            }
            int v2 = tokens[2].toInt(&ok);
            if(ok){
                e.seconds = v2;
            }
        }
    }
    return e;
}

QList<LogUploadModel> LogUploadModel::ParseList(const QString &txt)
{
    QList<LogUploadModel> e;
    bool valid = !txt.isEmpty();
    if(valid){
        QStringList lines = txt.split('\n');
        for(auto&a:lines){
            bool lineValid = !a.isEmpty() && !a.startsWith('#');
            if(lineValid){
                LogUploadModel item = Parse(a);
                e.append(item);
            }
        }
    }
    return e;
}
