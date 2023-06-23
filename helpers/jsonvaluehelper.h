#ifndef JSONVALUEHELPER_H
#define JSONVALUEHELPER_H

#include <QDateTime>
#include <QJsonObject>
#include <QString>

class JsonValueHelper
{
private:
    static bool TryGetValue(const QJsonObject &o, const QString &key, QJsonValue *value);
public:
    static bool TryGetVariant(const QJsonObject &o, const QString &key, QVariant *value);
};

#endif // JSONVALUEHELPER_H
