#ifndef FILENAMEHELPER_H
#define FILENAMEHELPER_H

#include <QString>

class FileNameHelper
{
private:
    static bool _inited;
    static QString _appDir;
public:
    static bool Init(const QString& appDir);
    static QString SettingsFileName();
    static QString GetSlideShowFileName();
    static QString GetCounterFileName(const QString &fn);
    static QString GetLogFileName(const QString &fn);
    static QString GetDownloadFolder();
    static QStringList GetDownloadFolderContent();
    static QString GetDownloadFileName(const QString &fn);
    static qint64 GetFileSize(const QString &fn);
    static QString GetSlideShowStateFileName();
    static void DeleteFile(const QString &fn);
};

#endif // FILENAMEHELPER_H
