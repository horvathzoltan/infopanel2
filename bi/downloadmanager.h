#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H


#include "pubimages.h"

#include <QList>
#include <QString>

class DownloadManager
{
private:
    QString _downloadFolder;
    PubImages _pubImages;

    QString GetDownload_CurlCommand(const QList<DownloadFileMetaData> &filelist);
public:
    DownloadManager();
    void Init(const QString& downloadFolder);
    void AddNewPubImageItems(const QList<DownloadFileMetaData>& fileList);
    bool Download_Curl(const QList<DownloadFileMetaData>& filelist);
    bool TryDownload();
};

#endif // DOWNLOADMANAGER_H
