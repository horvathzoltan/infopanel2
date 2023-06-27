#ifndef DEVICEREQUESTMODEL_H
#define DEVICEREQUESTMODEL_H

#include <QUuid>

class DeviceRequestModel
{
private:

    /// <summary>
    /// This ensures the webapi, that the request has been originated from a MobileFlex related application
    /// </summary>
    QUuid id;

    /// <summary>
    /// The globally unique identifier of the device.
    /// Since this is the primary key, please ensure that this value is constant always!
    /// </summary>
    QString deviceId;

    /// <summary>
    /// Firendly name of the current device (like Joe's phone, Imre's computer, Company Raspberry PI, etc...)
    /// </summary>
    QString deviceName;

public:
    DeviceRequestModel(QUuid _id,
                  const QString& _deviceId,
                  const QString& _deviceName);

    QString ToJson() const;
};

#endif // DEVICEREQUESTMODEL_H
