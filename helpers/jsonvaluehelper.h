#ifndef JSONVALUEHELPER_H
#define JSONVALUEHELPER_H

#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QString>

class JsonValueHelper
{
private:
    static bool TryGetValue(const QJsonObject &o, const QString &key, QJsonValue *value);
public:
    static bool TryGetVariant(const QJsonObject &o, const QString &key, QVariant *value);
    static bool TryGetJsonArray(const QJsonObject &o, const QString &key, QJsonArray *v);

    template<typename T>
    static bool QJsonArrayToList(const QJsonArray& jsonArray, QList<T>* retValue){
        bool valid = retValue!=nullptr;
        bool retVal = false;
        if(valid){
            retValue->clear();
            retVal = true;
            for (const QJsonValue &item_ref : jsonArray) {
                if(item_ref.isObject()){
                    QJsonObject jsonObject = item_ref.toObject();
                    T obj = T::JsonParse(jsonObject);
                    retValue->append(obj);
                }
            }
        }
        return retVal;
    }


    template<typename T>
    static bool TryGetEnum(const QVariant& var, T* v){
        bool valid = v != nullptr;// && var.type()==QVariant::Int;
        bool retVal = false;
        if(valid){
            bool ok2;
            int i = var.toLongLong(&ok2);
            if(ok2){
                * v=static_cast<T>(i);
                retVal = true;
            }
        }
        return retVal;
    }

};

#endif // JSONVALUEHELPER_H
