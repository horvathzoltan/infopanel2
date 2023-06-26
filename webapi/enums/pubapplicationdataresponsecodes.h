#ifndef PUBAPPLICATIONDATARESPONSECODES_H
#define PUBAPPLICATIONDATARESPONSECODES_H

enum PubApplicationDataResponseCodes:int
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


#endif // PUBAPPLICATIONDATARESPONSECODES_H
