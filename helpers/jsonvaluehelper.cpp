#include "jsonvaluehelper.h"

#include <QJsonArray>
#include <QJsonArray>
#include <QJsonArray>

bool JsonValueHelper::TryGetVariant(const QJsonObject &o, const QString&key, QVariant *v){
    bool retVal = false;
    bool valid = !o.isEmpty() && !key.isEmpty() && v!=nullptr;
    if(valid){        
        QJsonValue value;
        bool ok = TryGetValue(o, key, &value);
        if(ok){
            *v = value.toVariant();
            retVal = true;
        }
    }
    return retVal;
}

bool JsonValueHelper::TryGetValue(const QJsonObject &o, const QString&key, QJsonValue *v){
    bool retVal = false;
    bool valid = !o.isEmpty() && !key.isEmpty() && v!=nullptr;
    if(valid){
        QJsonValue value = o.value(key);
        if(!value.isUndefined()){
            *v = value;
            retVal = true;
        }
    }
    return retVal;
}


bool JsonValueHelper::TryGetJsonArray(const QJsonObject &o, const QString&key, QJsonArray *v){
    bool retVal = false;
    bool valid = !o.isEmpty() && !key.isEmpty() && v!=nullptr;
    if(valid){
        QJsonValue value = o.value(key);
        bool objValid = !value.isUndefined() && value.isArray();
        if(objValid){
            *v = value.toArray();
            retVal = true;
        }
    }
    return retVal;
}

