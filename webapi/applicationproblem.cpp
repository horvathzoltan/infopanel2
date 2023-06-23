#include "applicationproblem.h"
#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"


ApplicationProblem::ApplicationProblem()
{

}

ApplicationProblem ApplicationProblem::JsonParse(const QJsonObject &o)
{
    ApplicationProblem d;
    QVariant v;
    bool ok;

    //static const QString nameof_type =  NameOf::_nameof<0>("type", sizeof(type));


    static const QString nameof_type = nameof(type);
    static const QString nameof_title = nameof(title);
    static const QString nameof_status = nameof(status);
    static const QString nameof_detail = nameof(detail);
    static const QString nameof_instance = nameof(instance);

    ok = JsonValueHelper::TryGetVariant(o, nameof_type, &v);
    if(ok)d.type=v.toString();

    ok = JsonValueHelper::TryGetVariant(o, nameof_title, &v);
    if(ok)d.title=v.toString();

    ok = JsonValueHelper::TryGetVariant(o, nameof_status, &v);
    if(ok)d.status=v.toInt();

    ok = JsonValueHelper::TryGetVariant(o, nameof_detail, &v);
    if(ok)d.detail=v.toString();

    ok = JsonValueHelper::TryGetVariant(o, nameof_instance, &v);
    if(ok)d.instance=v.toString();

    for(auto&key:o.keys()){
        bool unknownKey = key != nameof_type &&
                          key != nameof_title &&
                          key != nameof_status &&
                          key != nameof_detail &&
                          key != nameof_detail;
        if(unknownKey){
            d._fields.insert(key, o.value(key).toString());
        }
    }

    return d;
}
