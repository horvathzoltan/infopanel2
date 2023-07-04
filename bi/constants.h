#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QUuid>

#include "helpers/networkhelper.h"

class Constants
{
private:
    QUuid _mobileFlexGuid = QUuid::fromString(QStringLiteral("7a0e0865-08b2-488a-8a20-c327ce28e59d"));
    QUuid _applicationId = QUuid::fromString(QStringLiteral("f83c031c-92ea-4f0c-8240-13427ea088a2"));
    //QUuid _applicationId_master = QUuid::fromString(QStringLiteral("f83c031c-92ea-4f0c-8240-13427ea088a1"));
    QString _deviceId = NetworkHelper::HwId();
    QString _piDeviceId = QStringLiteral("dca6327492ab");
    bool _isTestMode;
public:
    Constants();

    QUuid MobileFlexGuid(){return _mobileFlexGuid;}
    //QString DeviceId(){return _deviceId;}

    QString DeviceId(){return _deviceId;}
        //{ return IsTestMode()?_piDeviceId:_deviceId;}
    QUuid ApplicationId(){return _applicationId;}

    bool IsTestMode(){return _isTestMode;}
    void SetTestMode(bool v){_isTestMode = v;}
};

#endif // CONSTANTS_H
