#include "devicerequest.h"
#include "helpers/nameof.h"

#include <QJsonObject>
#include <QJsonDocument>

QString MetaHelper_GetRowName(const QString &n);

DeviceRequest::DeviceRequest(QUuid _id,
                             const QString& _deviceId,
                             const QString& _deviceName)
{    
    id = _id;
    deviceId = _deviceId;
    deviceName = _deviceName;
}

QString DeviceRequest::ToJson() const
{
    QJsonObject o;

    static const QString nameof_id = nameof(id);
    static const QString nameof_deviceId = nameof(deviceId);
    static const QString nameof_deviceName = nameof(deviceName);

    o.insert(nameof_id, id.toString(QUuid::WithoutBraces)+"}");
    o.insert(nameof_deviceId, deviceId);
    o.insert(nameof_deviceName, deviceName);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(o);
    QString str = jsonDoc.toJson();

    return str;
}
