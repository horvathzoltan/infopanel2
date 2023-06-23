#include "device.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

Device::Device()
{

}

Device Device::JsonParse(const QJsonObject &device)
{
    Device d;
    bool ok;
    QVariant v;

    static const QString nameof_deviceId = nameof(deviceId);
    static const QString nameof_deviceName = nameof(deviceName);
    static const QString nameof_active = nameof(active);
    static const QString nameof_lastDeviceLoginDate = nameof(lastDeviceLoginDate);
    static const QString nameof_comments = nameof(comments);
    static const QString nameof_applications = nameof(applications);

    ok = JsonValueHelper::TryGetVariant(device, nameof_deviceId, &v);
    if(ok) d.deviceId=v.toString();

    ok = JsonValueHelper::TryGetVariant(device, nameof_deviceName, &v);
    if(ok) d.deviceName=v.toString();

    ok = JsonValueHelper::TryGetVariant(device, nameof_active, &v);
    if(ok) d.active=v.toBool();

    ok = JsonValueHelper::TryGetVariant(device, nameof_lastDeviceLoginDate, &v);
    if(ok) d.lastDeviceLoginDate=v.toDateTime();

    ok = JsonValueHelper::TryGetVariant(device, nameof_comments, &v);
    if(ok) d.comments=v.toString();

    ok = JsonValueHelper::TryGetVariant(device, nameof_applications, &v);
    if(ok) d.applications=v.toString();

    return d;
}



