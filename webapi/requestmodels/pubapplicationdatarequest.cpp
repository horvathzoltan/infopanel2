#include "pubapplicationdatarequest.h"
#include "helpers/nameof.h"

#include <QJsonObject>
#include <QJsonDocument>

PubApplicationDataRequest::PubApplicationDataRequest(QUuid _id,
                                                     const QString& _deviceId,
                                                     const QUuid& _applicationId)
{
    id = _id;
    deviceId = _deviceId;
    applicationId = _applicationId;
}

QString PubApplicationDataRequest::ToJson() const
{
    QJsonObject o;

    static const QString nameof_id = nameof(id);
    static const QString nameof_deviceId = nameof(deviceId);
    static const QString nameof_applicationId = nameof(applicationId);

    o.insert(nameof_id, id.toString(QUuid::WithoutBraces));
    o.insert(nameof_deviceId, deviceId);
    o.insert(nameof_applicationId, applicationId.toString(QUuid::WithoutBraces));

    QJsonDocument jsonDoc;
    jsonDoc.setObject(o);
    QString str = jsonDoc.toJson();

    return str;
}
