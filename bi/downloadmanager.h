#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include "pubimages.h"
#include <QList>
#include <QString>
#include <QTimer>

class DownloadManager : public QObject
{
    Q_OBJECT

private:
    //QString _downloadFolder;
    DownloadFiles _filesToDownload;

    QString GetDownload_CurlCommand(const QList<DownloadFileMetaData> &filelist);
    QString GetDownloadMeta_CurlCommand(const QList<DownloadFileMetaData> &filelist);

    QTimer* _timer;
    bool _On_TimeoutGuard = false;
    QThread* _timerThread;

    static bool _isDownloading;

    bool _enabled;
    bool _verbose;


public:
    DownloadManager();//int downloadInterval);
    ~DownloadManager();

    void SetEnabled(bool v){_enabled=v;}
    void SetVerbose(bool v){_verbose=v;}

//    void Init(const QString& downloadFolder);
    void AddNewFilesToDownload(const QList<DownloadFileMetaData>& fileList);
    bool Download_Curl(const QList<DownloadFileMetaData>& filelist);
    QList<qint64> DownloadMeta_Curl(const QList<DownloadFileMetaData>& filelist);
    bool TryDownload();
    bool HasDownloads();
    void On_Timeout();

};

#endif // DOWNLOADMANAGER_H
