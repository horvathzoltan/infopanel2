#include "pubimageitem.h"

#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

PubImageItem::PubImageItem()
{

}

PubImageItem PubImageItem::JsonParse(const QJsonObject &jsonObject)
{
    PubImageItem d;
    bool ok;
    QVariant v;

    static const QString nameof_id = nameof(id);//
    static const QString nameof_imageUrl = nameof(imageUrl);
    static const QString nameof_displayTimeSconds = nameof(displayTimeSconds);

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_id, &v);
    if(ok) d.id=v.toUuid();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_imageUrl, &v);
    if(ok) d.imageUrl=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_displayTimeSconds, &v);
    if(ok) d.displayTimeSconds=v.toInt();

    return d;
}
