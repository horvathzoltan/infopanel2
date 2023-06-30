#include "deviceresponsemodel.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

DeviceResponseModel::DeviceResponseModel()
{

}

DeviceResponseModel DeviceResponseModel::JsonParse(const QJsonObject &o)
{
    DeviceResponseModel d;
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

Application* DeviceResponseModel::GetApplication(QUuid id)
{
    for(auto&a:this->device.applications){
        if (a.id == id) return &a;
    }
    return nullptr;
}


