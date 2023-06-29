#ifndef TESTMODE_H
#define TESTMODE_H

#include <QList>
#include <QObject>
#include "bi/downloadmanager.h"
#include "alivemanager.h"
#include "bi/slideshowitem.h"
#include "bi/slideshowmanager.h"
#include "mode.h"
#include "webapimanager.h"

class TestMode : public QObject, public Mode
{
    Q_OBJECT

private:
    WebApiManager *_webApiManager;
    DownloadManager _downloadManager;
    AliveManager _aliveManager;
    SlideshowManager _slideshowManager;
    DownloadFiles _pubImages;

    QString _lastApplicationDataVersion_Local;
    QString _lastApplicationDataVersion_Remote;
    QString _lastApplicationVersion;

    const Application *_application;    

public:
    TestMode(WebApiManager* webApiManager, QObject* p = nullptr);
    ~TestMode();
    bool IsInited(){return _webApiManager != nullptr;}

    bool Start();
    bool GetPubApplicationData();

    void On_NewApplicationDataAvailable();
    void On_NewApplicationDataRequired();
    static QList<DownloadFileMetaData> ToFilesToDownload(QList<PubImageItem> pubItems);
    static QList<SlideShowItem> ToFilesToSlideshow(QList<PubImageItem> pubItems);
};

#endif // TESTMODE_H
