#include "testmode.h"
#include "bi/constants.h"
#include "helpers/logger.h"
#include "settings.h"

#include <QDir>
#include <QScreen>
#include <QApplication>

extern Constants constants;
extern Settings settings;

TestMode::TestMode(WebApiManager* webApiManager, QObject*p): QObject(p), Mode(true),
    _downloadManager(), _aliveManager(webApiManager)
{
    _webApiManager = webApiManager;

    _cecManager.SetVerbose(settings.CecManagerVerbose());

    connect(&_aliveManager, &AliveManager::NewApplicationDataAvailable, this, &TestMode::On_NewApplicationDataAvailable);
    connect(&_aliveManager, &AliveManager::NewApplicationDataRequired, this, &TestMode::On_NewApplicationDataRequired);
    connect(&_aliveManager, &AliveManager::Alive, this, &TestMode::On_Alive);
    connect(&_slideshowManager, &SlideshowManager::ChangeImage, this, &TestMode::On_ChangeImage);
    connect(&_slideshowManager, &SlideshowManager::HideImage, this, &TestMode::On_HideImage);

    connect(&_cecManager, &CecManager::PowerOn, this, &TestMode::On_PowerOn);
    connect(&_cecManager, &CecManager::PowerOff, this, &TestMode::On_PowerOff);

    QList<QScreen*> screens = qApp->screens();

    if(screens.length()>0){
        for(QScreen* a:screens)
        {
            zInfo("screen_name:"+a->name());
        }

        bool isFullScreen = settings.SlaveFullSize();
        if(screens.length()>=2){
            _w1 = new Form3();
            QScreen *screen = screens[1];
            _w1->move(screen->geometry().x(), screen->geometry().y());
            if(isFullScreen){                
                _w1->resize(screen->geometry().width(), screen->geometry().height());
                _w1->showFullScreen();
            } else {
                _w1->show();
            }
        }

//        if(screens.length()>=2){
//            _w2 = new Frame2();
//            if(isFullScreen){
//                QScreen *screen = screens[1];
//                _w2->move(screen->geometry().x(), screen->geometry().y());
//                _w2->resize(screen->geometry().width(), screen->geometry().height());
//                _w2->showFullScreen();
//            } else {
//                _w2->show();
//            }
//        }
    }
}

TestMode::~TestMode()
{
    //delete(_downloadManager);
}

bool TestMode::Start()
{
    bool valid = IsInited();
    bool retVal = false;
    if(valid){
        zInfo("starting TestMode...");

        _lastApplicationDataVersion = _slideshowManager.GetSerieName();

        //_lastApplicationDataVersion = "Teszt.1";
        //QString deviceId = constants.IsTestMode()?"dca6327492ab":constants.DeviceId();
        
        DeviceRequestModel deviceRequest(
            constants.MobileFlexGuid(),
            constants.DeviceId(),
            settings.DeviceName());
        
        DeviceResponseModel deviceResponse;
        bool ok = _webApiManager->DeviceRequest(deviceRequest, &deviceResponse);
        if(ok){
            // online mode
            zInfo(QStringLiteral("deviceResponse: ")+QString::number(deviceResponse.resultCode));
            zInfo(QStringLiteral("deviceName: ")+deviceResponse.device.deviceName);
            //bool isAppValid = _webApiManager->ValidateApplication(deviceResponse);
            _application = _webApiManager->GetApplication(deviceResponse);

            bool isAppValid = _application!=nullptr;
            if(isAppValid){
                retVal = true;
                _aliveManager.SetApplicationVersion(_application->applicationVersion);
                _aliveManager.SetApplicationDataVersion(_application->applicationDataVersion);

                // induláskor, az applicationban kapunk erről információt
                // ha van letöltetlen adat le kell tölteni
                // ha jött új adat, hozzá kell adni a letöltendőkhöz
                bool isNewDataAvailable = _application->applicationDataVersion != _lastApplicationDataVersion;
                if(isNewDataAvailable){
                    zInfo("isNewDataAvailable:"+_lastApplicationDataVersion+"->"+_application->applicationDataVersion);
                    On_NewApplicationDataRequired();
                }
                bool isNewVersionAvailable = _application->applicationVersion != _lastApplicationVersion;
                if(isNewVersionAvailable){
                    zInfo("isNewVersionAvailable:"+_lastApplicationVersion+"->"+_application->applicationVersion);
                    //On_NewApplicationRequired();
                }

                _cecManager.SetEnabled(true);
                _aliveManager.Start();
                _slideshowManager.ReStart();
                _logManager.Start();
            } else{
                zInfo("no valid app");
            }
        }else{
            // offline mode
            zInfo(_webApiManager->LastErrorMessage()); // ebben van ok ami miatt nem online

            _slideshowManager.ReStart();
            _cecManager.SetEnabled(true);
            retVal = true;
        }

    }
    return retVal;
}

bool TestMode::Stop(){
    _slideshowManager.Stop();
    _downloadManager.SetEnabled(false);
    _aliveManager.Stop();
    _cecManager.SetEnabled(false);
    _logManager.Stop();

    _w1->HidePicture();
    return true;
}

bool TestMode::GetPubApplicationData()
{
    PubApplicationDataRequestModel pubApplicationDataRequest(
        constants.MobileFlexGuid(),
        constants.DeviceId(),
        constants.ApplicationId());

    // Alkalmazásadatok letöltése
    PubApplicationDataResponseModel pubApplicationDataResponse;
    bool pubDataOk = _webApiManager->PubApplicationDataRequest(pubApplicationDataRequest, &pubApplicationDataResponse);
    if(pubDataOk && pubApplicationDataResponse.resultCode == PubApplicationDataResponseModel::Codes::Ok){
        // a verziót letároljuk
        _lastApplicationDataVersion = pubApplicationDataResponse.pubApplicationData.applicationDataVersion;        
        _aliveManager.SetApplicationDataVersion(_lastApplicationDataVersion);

        auto slideshowSerie = _slideshowManager.GetSerieName();
        bool isChangeSerie = slideshowSerie !=_lastApplicationDataVersion;
        if(isChangeSerie){
            QList<DownloadFileMetaData> newPubImageItems = ToFilesToDownload(
                pubApplicationDataResponse.pubApplicationData.pubImageItems);
            _downloadManager.AddNewFilesToDownload(newPubImageItems);

            QList<SlideShowItem> images = ToFilesToSlideshow(
                pubApplicationDataResponse.pubApplicationData.pubImageItems);

            _slideshowManager.SetImages(_lastApplicationDataVersion, images);
            _slideshowManager.SaveImages();
        }

//        if(!_slideshowManager.IsStarted()){
//             _slideshowManager.ReStart();
//        }
    }
    return true;
}

QList<DownloadFileMetaData> TestMode::ToFilesToDownload(QList<PubImageItem> pubItems){
    QList<DownloadFileMetaData> retVal;
    for(auto&a:pubItems){
        DownloadFileMetaData item{.filename = a.id.toString(QUuid::WithoutBraces),
                                  .size = -1,
                                  .url=a.imageUrl };
        retVal.append(item);
    }
    return retVal;
}

QList<SlideShowItem> TestMode::ToFilesToSlideshow(QList<PubImageItem> pubItems)
{
    QList<SlideShowItem> retVal;
    QDir downloadDir(settings.DownloadDirectory());

    for(auto&a:pubItems){        
        QString fn = downloadDir.filePath(a.id.toString(QUuid::WithoutBraces));
        SlideShowItem item{.filename = fn,
                           .timeout = a.displayTimeSconds,
                           .id=a.id };
        retVal.append(item);
    }
    return retVal;
}

void TestMode::On_NewApplicationDataAvailable(){
    //zTrace();
    //_aliveManager.Stop();
    GetPubApplicationData();
    //_aliveManager.Start();
}

void TestMode::On_NewApplicationDataRequired(){    
    //zTrace();
    //_aliveManager.Stop();
    GetPubApplicationData();
    bool hasDownloads = _downloadManager.HasDownloads();
    if(hasDownloads){
        bool isDownloadOk = _downloadManager.TryDownload();
        zInfo(QStringLiteral("isDownloadOk:")+(isDownloadOk?"ok":"failed"));
    }
    //_aliveManager.Start();
}

void TestMode::On_Alive()
{
    bool start = !_slideshowManager.IsStarted() && _slideshowManager.ImagesLength()>0;
    if(start){
        _slideshowManager.ReStart();
    }
}

void TestMode::On_PowerOn()
{
    zInfo("CEC On_PowerOn");
    bool isSlideshowRunning = _slideshowManager.IsStarted();
    if(!isSlideshowRunning){
        _slideshowManager.ReStart();
    }
}

void TestMode::On_PowerOff()
{
    zInfo("CEC On_PowerOff");
    bool isSlideshowRunning = _slideshowManager.IsStarted();
    if(isSlideshowRunning){
        _slideshowManager.Stop();
    }
}

void TestMode::On_ChangeImage(){
    QString fn = _slideshowManager.GetCurrentImageName();
    QString sn = _slideshowManager.GetSerieName();
    QUuid id = _slideshowManager.GetCurrentId();
    int time = _slideshowManager.GetCurrentImageTime();
    _w1->ShowPicture(fn, sn+":"+QString::number(time)+"sec", id);
}

void TestMode::On_HideImage(){
    //QString fn = _slideshowManager.GetCurrentImageName();
    //QString sn = _slideshowManager.GetSerieName();
    //int time = _slideshowManager.GetCurrentImageTime();
    _w1->HidePicture();
}
