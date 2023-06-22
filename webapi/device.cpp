#include "device.h"

#include "helpers/jsonvaluehelper.h"

Device::Device()
{

}

Device Device::JsonParse(const QJsonObject &device)
{
    Device d;
    bool ok;
    QVariant v;

    ok = JsonValueHelper::TryGetVariant(device, "deviceId", &v);
    if(ok) d.deviceId=v.toString();
    ok = JsonValueHelper::TryGetVariant(device, "deviceName", &v);
    if(ok) d.deviceName=v.toString();
    ok = JsonValueHelper::TryGetVariant(device, "active", &v);
    if(ok) d.active=v.toBool();
    ok = JsonValueHelper::TryGetVariant(device, "lastDeviceLoginDate", &v);
    if(ok) d.lastDeviceLoginDate=v.toDateTime();
    ok = JsonValueHelper::TryGetVariant(device, "comments", &v);
    if(ok) d.comments=v.toString();
    ok = JsonValueHelper::TryGetVariant(device, "applications", &v);
    if(ok) d.applications=v.toString();

    return d;
}



