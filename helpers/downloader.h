#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QString>

class Downloader
{
public:
    struct Output
    {
        QString stdOut;
        QString stdErr;
        int exitCode;
        QString ToString();
    };

    static Output Execute(const QString& cmd, const QStringList& args, int timeout = -1);
    static bool Wget(const QString &url, const QString &filename);    
    static QString AvahiResolve(const QString &filename);


    struct DownloadFileName{
        QString filename;
        QString url;
    };

    static bool Download_Curl(const QString& downloadFolder, const QList<DownloadFileName>& filelist);
private:
    static QString GetDownload_CurlCommand(const QString& downloadFolder, const QList<DownloadFileName> &filelist);
};

#endif // DOWNLOADER\_H
