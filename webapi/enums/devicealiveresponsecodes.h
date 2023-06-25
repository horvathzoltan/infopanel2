#ifndef DEVICEALIVERESPONSECODES_H
#define DEVICEALIVERESPONSECODES_H

enum DeviceAliveResponseCodes:int
{
    Ok = 0x00,
    InvalidRequestGuid = 0x01,
    SqlError = 0x02,
    DeviceError = 0x04,
    NewApplicationVersionAvailable = 0x10,
    NewApplicationVersionRequired = 0x20,
    NewApplicationDataAvailable = 0x40,
    NewApplicationDataRequired = 0x80,
};


#endif // DEVICEALIVERESPONSECODES_H
