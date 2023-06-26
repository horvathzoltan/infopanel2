#include "devicealiveresponse.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

DeviceAliveResponse::DeviceAliveResponse()
{

}

DeviceAliveResponse DeviceAliveResponse::JsonParse(const QJsonObject &jsonObject)
{
    DeviceAliveResponse d;
    QVariant v;
    bool ok;

    static const QString nameof_resultCode = nameof(resultCode);

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_resultCode, &v);
    if(ok) JsonValueHelper::TryGetEnum<DeviceAliveResponseCodes>(v, &d.resultCode);

    return d;
}
