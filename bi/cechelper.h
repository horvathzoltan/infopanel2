#ifndef CECHELPER_H
#define CECHELPER_H

#include <QString>



class CECHelper
{
public:
    static int GetPowerState(int device);
    static bool GetPowerState_2(int device);
    static QString GetValue(const QString& str, const QString &token, const QChar& sep);
    static bool SetPowerState(int device, int v);
    static QString GetDevice(int device);
};

#endif // CECHELPER_H
