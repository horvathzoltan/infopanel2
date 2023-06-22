#include "deviceresponse.h"

#include "helpers/jsonvaluehelper.h"

DeviceResponse::DeviceResponse()
{

}

DeviceResponse DeviceResponse::JsonParse(const QJsonObject &o)
{
    DeviceResponse d;
    QVariant v;
    bool ok;

    ok = JsonValueHelper::TryGetVariant(o, "resultCode", &v);
    if(ok){
        bool ok2;
        int i = v.toInt(&ok2);
        if(ok2){
            d.resultCode=static_cast<DeviceResponseCodes>(i);
        }
    }

    QJsonObject deviceObj = o.value("device").toObject();
    d.device = Device::JsonParse(deviceObj);
    return d;
}


