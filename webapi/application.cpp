#include "application.h"

#include "helpers/nameof.h"
#include "helpers/jsonvaluehelper.h"

#include <QJsonArray>


Application::Application()
{

}

Application Application::JsonParse(const QJsonObject &jsonObject)
{    
    Application d;
    bool ok;
    QVariant v;

    static const QString nameof_id = nameof(id);
    static const QString nameof_applicationName = nameof(applicationName);
    static const QString nameof_applicationTitle = nameof(applicationTitle);
    static const QString nameof_applicationLead = nameof(applicationLead);//
    static const QString nameof_applicationDescription = nameof(applicationDescription);//
    static const QString nameof_applicationVersion = nameof(applicationVersion);//
    static const QString nameof_applicationDataVersion = nameof(applicationDataVersion);//
    static const QString nameof_applicationEnabledLoginFlag = nameof(applicationEnabledLoginFlag);//
    static const QString nameof_loginUrl = nameof(loginUrl);//
    static const QString nameof_mainUrl = nameof(mainUrl);//
    static const QString nameof_settingsUrl = nameof(settingsUrl);//
    static const QString nameof_helpUrl = nameof(helpUrl);//
    static const QString nameof_applicationThemes = nameof(applicationThemes);//
    static const QString nameof_defaultThemeId = nameof(defaultThemeId);//
    static const QString nameof_logoUrl = nameof(logoUrl);//
    static const QString nameof_applicationUrl = nameof(applicationUrl);
    static const QString nameof_applicationDataUrl = nameof(applicationDataUrl);

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_id, &v);
    if(ok) d.id=v.toUuid();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationName, &v);
    if(ok) d.applicationName=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationTitle, &v);
    if(ok) d.applicationTitle=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationLead, &v);
    if(ok) d.applicationLead=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationDescription, &v);
    if(ok) d.applicationDescription=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationVersion, &v);
    if(ok) d.applicationVersion=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationDataVersion, &v);
    if(ok) d.applicationDataVersion=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationEnabledLoginFlag, &v);
    if(ok) d.applicationEnabledLoginFlag=v.toInt();//

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_loginUrl, &v);
    if(ok) d.loginUrl=v.toString();//

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_mainUrl, &v);
    if(ok) d.mainUrl=v.toString();//

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_settingsUrl, &v);
    if(ok) d.settingsUrl=v.toString();//

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_helpUrl, &v);
    if(ok) d.helpUrl=v.toString();//helpUrl

//    QJsonArray applicationThemes_JsonArray = jsonObject.value(nameof_applicationThemes).toArray();
//    for (QJsonValueRef applicationTheme_ref : applicationThemes_JsonArray) {
//        ApplicationTheme applicationTheme = ApplicationTheme::JsonParse(applicationTheme_ref);
//        d.applicationThemes.append(applicationTheme);
//    }

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_defaultThemeId, &v);
    if(ok) d.defaultThemeId=v.toInt();// defaultThemeId

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_logoUrl, &v);
    if(ok) d.logoUrl=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationUrl, &v);
    if(ok) d.applicationUrl=v.toString();

    ok = JsonValueHelper::TryGetVariant(jsonObject, nameof_applicationDataUrl, &v);
    if(ok) d.applicationDataUrl=v.toString();


    return d;
}
