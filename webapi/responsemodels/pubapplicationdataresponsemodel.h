#ifndef PUBAPPLICATIONDATARESPONSEMODEL_H
#define PUBAPPLICATIONDATARESPONSEMODEL_H

#include "webapi/pubapplicationdata.h"

#include <QJsonObject>

class PubApplicationDataResponseModel
{
public:
    enum Codes:int
    {
        // general response codes
        Undefined = -1,
        Ok = 0,
        InvalidRequestGuid,
        SqlError,
        DataServiceInstanceDoesNotExist,

        // device related error codes
        DeviceDoesNotExists = 100,
        DeviceInactive,
        DeviceAccessDenied,

        // pub specific codes
    };


    /// <summary>
    /// The result code of the webapi call for the pub response
    /// </summary>
    Codes resultCode = Codes::Undefined;

    /// <summary>
    /// Contains the images and display times for the pub project
    /// </summary>
    PubApplicationData pubApplicationData;// { get; set; } = null;

public:
    PubApplicationDataResponseModel();
    
    static PubApplicationDataResponseModel JsonParse(const QJsonObject& o);
};

#endif // PUBAPPLICATIONDATARESPONSEMODEL_H
