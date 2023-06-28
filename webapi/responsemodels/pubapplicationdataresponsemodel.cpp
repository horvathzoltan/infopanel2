#include "webapi/responsemodels/pubapplicationdataresponsemodel.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

PubApplicationDataResponseModel::PubApplicationDataResponseModel()
{

}

PubApplicationDataResponseModel PubApplicationDataResponseModel::JsonParse(const QJsonObject &o)
{
    PubApplicationDataResponseModel d;
    QVariant v;
    bool ok;

    static const QString nameof_resultCode = nameof(resultCode);
    static const QString nameof_pubApplicationData = nameof(pubApplicationData);

    ok = JsonValueHelper::TryGetVariant(o, nameof_resultCode, &v);
    if(ok){
        bool ok2;
        int i = v.toInt(&ok2);
        if(ok2){
            d.resultCode=static_cast<PubApplicationDataResponseModel::Codes>(i);
        }
    }

    QJsonObject deviceObj = o.value(nameof_pubApplicationData).toObject();
    d.pubApplicationData = PubApplicationData::JsonParse(deviceObj);
    return d;
}
