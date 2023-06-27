#include "devicealiveresponsemodel.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

DeviceAliveResponseModel::DeviceAliveResponseModel()
{

}

DeviceAliveResponseModel DeviceAliveResponseModel::JsonParse(const QJsonObject &jsonObject)
{
    DeviceAliveResponseModel d;
    QVariant v;
    bool ok;

    static const QString nameof_resultCode = nameof(resultCode);

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_resultCode, &v);
    if(ok) JsonValueHelper::TryGetEnum<DeviceAliveResponseModel::Codes>(v, &d.resultCode);

    return d;
}
