#ifndef CECHELPER_H
#define CECHELPER_H

#include <QString>



class CECHelper
{
public:
    static int GetPowerState();
    static bool GetPowerState_2();
    static QString GetValue(const QString& str, const QString &token, const QChar& sep);
    static bool SetPowerState(int v);
};

#endif // CECHELPER_H
