#ifndef PUBAPPLICATIONDATAREQUESTMODEL_H
#define PUBAPPLICATIONDATAREQUESTMODEL_H

#include <QUuid>

class PubApplicationDataRequestModel
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

public:
    PubApplicationDataRequestModel(QUuid _id,
                              const QString& _deviceId,
                              const QUuid& _applicationId);

    QString ToJson() const;
};

#endif // PUBAPPLICATIONDATAREQUESTMODEL_H
