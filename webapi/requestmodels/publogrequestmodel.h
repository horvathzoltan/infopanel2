#ifndef PUBLOGREQUESTMODEL_H
#define PUBLOGREQUESTMODEL_H

#include "webapi/loguploadmodel.h"
#include <QUuid>

class PubLogRequestModel
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
    /// The list of log items
    /// </summary>
    QList<LogUploadModel> logItems;// { get; set; } = new List<LogUpload>();


public:
    PubLogRequestModel(QUuid _id,
                       const QString& _deviceId,
                       const QUuid& _applicationId);

    QString ToJson() const;
};

#endif // PUBLOGREQUESTMODEL_H
