#ifndef APPLICATION_H
#define APPLICATION_H

#include "applicationtheme.h"

#include <QUuid>
#include <QString>
#include <QVariant>
#include <QList>

class Application
{
public:
    /// <summary>
    /// Applicaiton guid id
    /// </summary>
    QUuid id;// { get; set; }

    /// <summary>
    /// Application name (internal name, not for displaying)
    /// </summary>
    QString applicationName;// { get; set; } = string.Empty;

    /// <summary>
    ///  Applicaiton title
    /// </summary>
    QString applicationTitle;//;// { get; set; } = string.Empty;

    /// <summary>
    /// A brief explosure of the application and its using
    /// </summary>
    QString applicationLead;// { get; set; } = string.Empty;

    /// <summary>
    ///  Application description (using in later version)
    /// </summary>
    QString applicationDescription;// { get; set; } = string.Empty;

    /// <summary>
    ///  Version number of the application
    /// </summary>
    QString applicationVersion;// { get; set; } = string.Empty;

    /// <summary>
    ///  Version number of the application data
    /// </summary>
    QString applicationDataVersion;// { get; set; } = string.Empty;

    /// <summary>
    /// The login modes which are enabled when this application requires login
    /// </summary>
    //LoginModeEnum applicationEnabledLoginFlag;// { get; set; } = LoginModeEnum.NotRequired;
    int applicationEnabledLoginFlag;// { get; set; } = LoginModeEnum.NotRequired;

    /// <summary>
    /// The url for webapi access of login function
    /// Can be null, if the ApplicationEnabledLoginFlag = LoginModeEnum.NotRequired;
    /// </summary>
    QString loginUrl;// { get; set; } = null;

    /// <summary>
    /// The url which must be displayed in the main window
    /// </summary>
    QString mainUrl;// { get; set; } = string.Empty;

    /// <summary>
    /// The url which must be displayed if the user requests settings
    /// </summary>
    QString settingsUrl;// { get; set; } = null;

    /// <summary>
    /// The url which must be displayed if the user requests help
    /// </summary>
    QString helpUrl;// { get; set; } = null;

    /// <summary>
    /// Array of the applicable application themes
    /// The first element in the array is the default, in a later version we will support theme changing
    /// </summary>
    QList<ApplicationTheme> applicationThemes;// { get; set; } = null;

    /// <summary>
    /// If there are themes, then the default theme Id
    /// </summary>
    int defaultThemeId;// { get; set; } = null;

    /// <summary>
    /// The logo which can be displayed by this theme
    /// If the value is null, then the application defined logo should be used
    /// SVG format
    /// </summary>
    QString logoUrl;// { get; set; }

    /// <summary>
    /// The url where from the application can be downloaded and upgraded/installed
    /// </summary>
    QString applicationUrl;// { get; set; }

    /// <summary>
    /// The url where from the application data can be downloaded and upgraded/installed
    /// </summary>
    QString applicationDataUrl;// { get; set; }

public:
    Application();

    static QList<Application> JsonParse(QJsonArray applicationArray);
};

#endif // APPLICATION_H
