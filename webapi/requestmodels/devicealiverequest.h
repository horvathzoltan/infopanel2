#ifndef DEVICEALIVEREQUEST_H
#define DEVICEALIVEREQUEST_H

#include <QUuid>



class DeviceAliveRequest
{
public:
    /// <summary>
    /// This ensures the webapi, that the request has been originated from a MobileFlex related application
    /// </summary>
    QUuid id;// { get; set; } = Constants.MobileFlexGuid;

    /// <summary>
    /// The globally unique identifier of the device.
    /// Since this is the primary key, please ensure that this value is constant always!
    /// </summary>
    QString deviceId;// { get; set; } = string.Empty;

    /// <summary>
    /// Applicaiton guid id
    /// </summary>
    QUuid applicationId;// { get; set; }

    /// <summary>
    /// version number of the application currently in use
    /// </summary>
    QString applicationVersion;// { get; set; } = string.Empty;

    /// <summary>
    /// version number of the data, which is currently in use
    /// </summary>
    QString applicationDataVersion;// { get; set; } = string.Empty;

public:
    DeviceAliveRequest(QUuid _id,
                       const QString& _deviceId,
                       const QUuid& _applicationId);

    QString ToJson() const;
};

#endif // DEVICEALIVEREQUEST_H
