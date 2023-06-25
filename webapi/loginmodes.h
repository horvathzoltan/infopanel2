#ifndef LOGINMODES_H
#define LOGINMODES_H

enum LoginModeFlags:int
{
    NotRequired = 0,
    AccountAndPassword = 1,
    Pin = 2,
    Rfid = 4,
    Barcode = 8,
    Key = 16,
    FingerPrint = 32,
};


#endif // LOGINMODES_H
