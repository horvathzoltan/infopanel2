#ifndef APPLICATIONTHEME_H
#define APPLICATIONTHEME_H

#include <QString>
#include <QUuid>

class ApplicationTheme
{
public:
        /// <summary>
    /// Theme id
    /// </summary>
    int id;// { get; set; }

    /// <summary>
    /// Application Id, where this theme belongs to
    /// </summary>
    QUuid applicationId;// { get; set; }

    /// <summary>
    /// The logo which can be displayed by this theme
    /// If the value is null, then the application defined logo should be used
    /// </summary>
    QString logoUrl;// { get; set; }

    /// <summary>
    /// Hame of the theme
    /// </summary>
    QString name;// { get; set; } = string.Empty;

    // Rendering properties in strings (ARGB format)
    /// <summary>
    /// Background color of hte controls and the application page
    /// </summary>
    QString backgroundColor;// { get; set; } = "FFFFFFFF";

    /// <summary>
    /// Background gradient (secondary) color of hte controls and the application page
    /// Vertical Gradient should be created from BackgroundColor and BackgroundGradientColor
    /// </summary>
    QString backgroundGradientColor;// { get; set; } = "FFFFFFCC";

    /// <summary>
    /// Foreground color of hte controls and the application page
    /// </summary>
    QString foregroundColor;// { get; set; } = "FF000000";

    /// <summary>
    /// Background color of the buttons
    /// </summary>
    QString buttonBackgroundColor;// { get; set; } = "FF040804";

    /// <summary>
    /// Background gradient (secondary) color of the buttons
    /// Horizontal Gradient should be created from ButtonBackgroundColor and ButtonBackgroundGradientColor
    /// </summary>
    QString buttonBackgroundGradientColor;// { get; set; } = "FF020402";

    /// <summary>
    /// Foreground color of the button text
    /// </summary>
    QString buttonForegroundColor;// { get; set; } = "FFFFFF08";

    /// <summary>
    /// Color of the controls (input and others)
    /// </summary>
    QString controlColor;// { get; set; } = "FF000000";

public:
    ApplicationTheme();
};

#endif // APPLICATIONTHEME_H
