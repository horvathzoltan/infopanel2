#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QUuid>

#include "helpers/networkhelper.h"

class Constants
{
private:
    QUuid _mobileFlexGuid = QUuid::fromString(QStringLiteral("7a0e0865-08b2-488a-8a20-c327ce28e59d"));
    QString _deviceId = NetworkHelper::hwid_ethernet();
    bool _isTestMode;
public:
    Constants();

    QUuid MobileFlexGuid(){return _mobileFlexGuid;}
    QString DeviceId(){return _deviceId;}

    bool IsTestMode(){return _isTestMode;}
    void SetTestMode(bool v){_isTestMode = v;}
};

#endif // CONSTANTS_H
