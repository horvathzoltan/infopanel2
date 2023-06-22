#ifndef DEVICERESPONSECODES_H
#define DEVICERESPONSECODES_H

enum DeviceResponseCodes:int{
    SpecifyGlobalUrl = -99,
    Undefined = -1,
    Ok = 0,
    InvalidRequestGuid,
    SqlError,
    DataServiceInstanceDoesNotExist,
    DeviceDoesNotExists = 100,
    DeviceInactive,
    DeviceAccessDenied,
};


#endif // DEVICERESPONSECODES_H
