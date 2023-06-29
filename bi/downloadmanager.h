#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H


#include "pubimages.h"

#include <QList>
#include <QString>

class DownloadManager
{
private:
    QString _downloadFolder;
    DownloadFiles _filesToDownload;

    QString GetDownload_CurlCommand(const QList<DownloadFileMetaData> &filelist);
    QString GetDownloadMeta_CurlCommand(const QList<DownloadFileMetaData> &filelist);
public:
    DownloadManager(const QString &downloadFolder);
//    void Init(const QString& downloadFolder);
    void AddNewFilesToDownload(const QList<DownloadFileMetaData>& fileList);
    bool Download_Curl(const QList<DownloadFileMetaData>& filelist);
    QList<qint64> DownloadMeta_Curl(const QList<DownloadFileMetaData>& filelist);
    bool TryDownload();
    bool HasDownloads();
};

#endif // DOWNLOADMANAGER_H
