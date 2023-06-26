#ifndef PUBAPPLICATIONDATARESPONSE_H
#define PUBAPPLICATIONDATARESPONSE_H

#include "webapi/pubapplicationdata.h"
#include "webapi/enums/pubapplicationdataresponsecodes.h"

#include <QJsonObject>

class PubApplicationDataResponse
{
    /// <summary>
    /// The result code of the webapi call for the pub response
    /// </summary>
    PubApplicationDataResponseCodes resultCode;// { get; set; } = PubApplicationDataResponseCodes.Undefined;

    /// <summary>
    /// Contains the images and display times for the pub project
    /// </summary>
    PubApplicationData pubApplicationData;// { get; set; } = null;

public:
    PubApplicationDataResponse();

    static PubApplicationDataResponse JsonParse(const QJsonObject& o);
};

#endif // PUBAPPLICATIONDATARESPONSE_H
