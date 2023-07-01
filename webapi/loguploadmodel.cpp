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
