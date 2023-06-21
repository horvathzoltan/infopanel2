#ifndef FILENAMEHELPER_H
#define FILENAMEHELPER_H

#include <QString>

class FileNameHelper
{
    static bool _inited;
    static QString _appDir;
public:
    static bool Init(const QString& appDir);
    static QString SettingsFileName();
};

#endif // FILENAMEHELPER_H
