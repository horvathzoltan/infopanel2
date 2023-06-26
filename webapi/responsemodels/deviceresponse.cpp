#include "deviceresponse.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

DeviceResponse::DeviceResponse()
{

}

DeviceResponse DeviceResponse::JsonParse(const QJsonObject &o)
{
    DeviceResponse d;
    QVariant v;
    bool ok;

    static const QString nameof_resultCode = nameof(resultCode);
    static const QString nameof_device = nameof(device);

    ok = JsonValueHelper::TryGetVariant(o, nameof_resultCode, &v);
    JsonValueHelper::TryGetEnum(v, &d.resultCode);

    QJsonObject deviceObj = o.value(nameof_device).toObject();
    d.device = Device::JsonParse(deviceObj);
    return d;
}


