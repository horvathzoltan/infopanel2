#include "testmode.h"
#include "bi/constants.h"
#include "helpers/logger.h"
#include "settings.h"

#include "helpers/downloader.h"



extern Constants constants;
extern Settings settings;

TestMode::TestMode(WebApiManager* webApiManager, QObject*p): QObject(p), Mode(true)
{
    _webApiManager = webApiManager;
}

TestMode::~TestMode()
{

}

bool TestMode::Start()
{
    bool valid = IsInited();
    bool retVal = false;
    if(valid){
        zInfo("starting TestMode...");

        QString deviceId = constants.IsTestMode()?"dca6327492ab":constants.DeviceId();
        
        DeviceRequestModel deviceRequest(
            constants.MobileFlexGuid(),
            deviceId,
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

                bool toDownload = _pubImageItems.empty() || _lastApplicationDataVersion_Remote >_lastApplicationDataVersion_Local;
                if(toDownload){
                    PubApplicationDataRequestModel pubApplicationDataRequest(
                        constants.MobileFlexGuid(),
                        deviceId,
                        constants.ApplicationId());

                    PubApplicationDataResponseModel pubApplicationDataResponse;
                    bool pubDataOk = _webApiManager->PubApplicationDataRequest(pubApplicationDataRequest, &pubApplicationDataResponse);
                    if(pubDataOk && pubApplicationDataResponse.resultCode == PubApplicationDataResponseModel::Codes::Ok){
                        _lastApplicationDataVersion_Local=pubApplicationDataResponse.pubApplicationData.applicationDataVersion;

                        _pubImageItems = pubApplicationDataResponse.pubApplicationData.pubImageItems;
                        //_pubImageItems.clear();
                        //_pubImageItems.append(pubApplicationDataResponse.pubApplicationData.pubImageItems);

                        QList<Downloader::DownloadFileName> downloads;
                        for(auto&a:_pubImageItems){
                            Downloader::DownloadFileName item;
                            item.filename = a.id.toString(QUuid::WithoutBraces);
                            item.url = a.imageUrl;
                            downloads.append(item);
                        }
                        bool isDownloadOk = Downloader::Download_Curl("~/pubImageItems", downloads);

                        zInfo(QStringLiteral("isDownloadOk:")+(isDownloadOk?"ok":"failed"));
                   }
                }
            }
        }else{
            zInfo(_webApiManager->LastErrorMessage());
        }

    }
    return retVal;
}
