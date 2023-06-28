#include "pubapplicationdata.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>


PubApplicationData::PubApplicationData()
{

}

PubApplicationData PubApplicationData::JsonParse(const QJsonObject &jsonObject)
{
    PubApplicationData d;
    QVariant v;
    bool ok;

    static const QString nameof_applicationDataVersion = nameof(applicationDataVersion);
    static const QString nameof_pubImageItems = nameof(pubImageItems);


    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationDataVersion, &v);
    if(ok) d.applicationDataVersion=v.toString();

    QJsonArray ja;
    ok = JsonValueHelper::TryGetJsonArray(jsonObject, nameof_pubImageItems, &ja);
    if(ok){
        JsonValueHelper::QJsonArrayToList(ja, &d.pubImageItems);
    }

    return d;
}
