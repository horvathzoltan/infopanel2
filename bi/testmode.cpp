#include "testmode.h"
#include "bi/constants.h"
#include "helpers/logger.h"
#include "settings.h"

#include <QDir>


extern Constants constants;
extern Settings settings;

TestMode::TestMode(WebApiManager* webApiManager, QObject*p): QObject(p), Mode(true),
    _downloadManager(settings.DownloadDirectory()), _aliveManager(webApiManager)
{
    _webApiManager = webApiManager;    

    connect(&_aliveManager, &AliveManager::NewApplicationDataAvailable, this, &TestMode::On_NewApplicationDataAvailable);
    connect(&_aliveManager, &AliveManager::NewApplicationDataRequired, this, &TestMode::On_NewApplicationDataRequired);
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

        //QString deviceId = constants.IsTestMode()?"dca6327492ab":constants.DeviceId();
        
        DeviceRequestModel deviceRequest(
            constants.MobileFlexGuid(),
            constants.DeviceId(),
            settings.DeviceName());
        
        DeviceResponseModel deviceResponse;
        bool ok = _webApiManager->DeviceRequest(deviceRequest, &deviceResponse);
        if(ok){
            zInfo(QStringLiteral("deviceResponse: ")+QString::number(deviceResponse.resultCode));
            zInfo(QStringLiteral("deviceName: ")+deviceResponse.device.deviceName);
            //bool isAppValid = _webApiManager->ValidateApplication(deviceResponse);
            _application = _webApiManager->GetApplication(deviceResponse);
            bool isAppValid = _application!=nullptr;

            zInfo(QStringLiteral("isAppValid:")+(isAppValid?"true":"false"));
            if(isAppValid){
                retVal = true;

                _lastApplicationVersion=_application->applicationVersion;
                _lastApplicationDataVersion_Remote=_application->applicationDataVersion;

                // induláskor, az applicationban kapink erről információt
                // ha van letöltetlen adat le kell tölteni
                // ha jött új adat, hozzá kell adni a letöltendőkhöz
                bool isNewDataAvailable = _lastApplicationDataVersion_Remote != _lastApplicationDataVersion_Local;
                if(isNewDataAvailable){
                    On_NewApplicationDataRequired();
                }
                _aliveManager.Start();
                //_downloadManager.Images();
                _slideshowManager.Start();
            }
        }else{
            zInfo(_webApiManager->LastErrorMessage());
        }

    }
    return retVal;
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
        _lastApplicationDataVersion_Local = pubApplicationDataResponse.pubApplicationData.applicationDataVersion;

        auto newPubImageItems = ToFilesToDownload(pubApplicationDataResponse.pubApplicationData.pubImageItems);

        _downloadManager.AddNewPubImageItems(newPubImageItems);
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

        auto filenamelist = downloadDir.entryList(QDir::Files);

        SlideShowItem item{.filename = a.id.toString(QUuid::WithoutBraces),
                           .timeout = a.displayTimeSconds };
        retVal.append(item);
    }
    return retVal;
}

void TestMode::On_NewApplicationDataAvailable(){
    zTrace();
    GetPubApplicationData();
}

void TestMode::On_NewApplicationDataRequired(){
    zTrace();
    GetPubApplicationData();
    bool hasDownloads = _downloadManager.HasDownloads();
    if(hasDownloads){
        bool isDownloadOk = _downloadManager.TryDownload();
        zInfo(QStringLiteral("isDownloadOk:")+(isDownloadOk?"ok":"failed"));
    }
}
