#include "applicationproblem.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"
#include <QVariantMap>
#include <QJsonDocument>

ApplicationProblem::ApplicationProblem()
{

}

ApplicationProblem ApplicationProblem::JsonParse(const QJsonObject &o)
{
    ApplicationProblem d;
    QVariant v;
    bool ok;

    //static const QString nameof_type =  NameOf::_nameof<0>("type", sizeof(type));


    static const QString nameof_type = nameof(type);
    static const QString nameof_title = nameof(title);
    static const QString nameof_status = nameof(status);
    static const QString nameof_detail = nameof(detail);
    static const QString nameof_instance = nameof(instance);

    ok = JsonValueHelper::TryGetVariant(o, nameof_type, &v);
    if(ok)d.type=v.toString();

    ok = JsonValueHelper::TryGetVariant(o, nameof_title, &v);
    if(ok)d.title=v.toString();

    ok = JsonValueHelper::TryGetVariant(o, nameof_status, &v);
    if(ok)d.status=v.toInt();

    ok = JsonValueHelper::TryGetVariant(o, nameof_detail, &v);
    if(ok)d.detail=v.toString();

    ok = JsonValueHelper::TryGetVariant(o, nameof_instance, &v);
    if(ok)d.instance=v.toString();

    for(auto&key:o.keys()){
        bool unknownKey = key != nameof_type &&
                          key != nameof_title &&
                          key != nameof_status &&
                          key != nameof_detail &&
                          key != nameof_detail;
        if(unknownKey && !o.isEmpty()){
            auto jsonValue = o.value(key);//.toString();

            if(jsonValue.isObject()){
//                auto m = jsonValue.toVariant();
//                d._fields.insert(key, m);
//            } else if(jsonValue.isArray()){
//                auto m = jsonValue.toVariant();
//                d._fields.insert(key, m);
//            }else{
                QVariant var = jsonValue.toVariant();
                d._fields.insert(key, var);
            }
        }
    }

    return d;
}

QStringList ApplicationProblem::GetErrors()
{
    QStringList retVal;
    QVariant value;
    if(_fields.contains("error")){
        value = _fields.value("error");
    } else if(_fields.contains("errors")){
        value = _fields.value("errors");
    }

    QVariant::Type t = value.type();
    if(t == QVariant::Map)
    {
        QMap<QString, QVariant> map = value.toMap();
        auto keys = map.keys();
        for (QVariant &a : map) {
            auto tt = a.type();
            if(tt == QVariant::List){
                retVal.append(a.toStringList());
            } else{
                retVal.append(a.toString());
            }
        }
    } else{
         retVal.append(value.toString());
    }
    return retVal;
}

QStringList ApplicationProblem::ErrorHandler(const QString& err){
    QStringList retVal;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(err.toUtf8());
    bool isJsonObject = jsonDocument.isObject();
    if (isJsonObject) {
        QJsonObject jsonObject = jsonDocument.object();
        ApplicationProblem _lastErr = ApplicationProblem::JsonParse(jsonObject);
        retVal = _lastErr.GetErrors();
    }
    else{
        retVal.append(err);
    }
    return retVal;
}
/*


















*/
