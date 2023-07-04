#ifndef TESTMODE_H
#define TESTMODE_H

#include <QList>
#include <QObject>
#include "bi/downloadmanager.h"
#include "alivemanager.h"
#include "bi/logmanager.h"
#include "bi/slideshowitem.h"
#include "bi/slideshowmanager.h"
#include "mode.h"
#include "webapimanager.h"
#include "cecmanager.h"

#include "form3.h"
//#include "frame2.h"

class TestMode : public QObject, public Mode
{
    Q_OBJECT

private:
    WebApiManager *_webApiManager;
    DownloadManager _downloadManager;
    AliveManager _aliveManager;
    SlideshowManager _slideshowManager;
    LogManager _logManager;
    CecManager _cecManager;

    DownloadFiles _pubImages;


    QString _lastApplicationDataVersion;
    //QString _lastApplicationDataVersion_Remote;
    QString _lastApplicationVersion;

    Form3* _w1 = nullptr;
    //Frame2* _w2 = nullptr;

    Application *_application;

public:
    TestMode(WebApiManager* webApiManager, QObject* p = nullptr);
    ~TestMode();
    bool IsInited(){return _webApiManager != nullptr;}

    bool Start();
    bool GetPubApplicationData();

    void On_NewApplicationDataAvailable();
    void On_NewApplicationDataRequired();
    void On_Alive();
    void On_PowerOn();
    void On_PowerOff();
    static QList<DownloadFileMetaData> ToFilesToDownload(QList<PubImageItem> pubItems);
    static QList<SlideShowItem> ToFilesToSlideshow(QList<PubImageItem> pubItems);
    void On_ChangeImage();
    void On_HideImage();
    bool Stop();
};

#endif // TESTMODE_H
