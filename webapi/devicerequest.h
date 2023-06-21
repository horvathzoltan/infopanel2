#ifndef DEVICEREQUEST_H
#define DEVICEREQUEST_H

#include <QUuid>



class DeviceRequest
{
private:

    /// <summary>
    /// This ensures the webapi, that the request has been originated from a MobileFlex related application
    /// </summary>
    QUuid Id;// { get; set; } = Constants.MobileFlexGuid;//"7a0e0865-08b2-488a-8a20-c327ce28e59d"

    /// <summary>
    /// The globally unique identifier of the device.
    /// Since this is the primary key, please ensure that this value is constant always!
    /// </summary>
    QString DeviceId;// { get; set; } = string.Empty;

    /// <summary>
    /// Firendly name of the current device (like Joe's phone, Imre's computer, Company Raspberry PI, etc...)
    /// </summary>
    QString DeviceName;// { get; set; } = string.Empty;

public:
    DeviceRequest();
};

#endif // DEVICEREQUEST_H
