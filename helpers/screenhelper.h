#ifndef SCREENHELPER_H
#define SCREENHELPER_H

#include <QString>
#include <QScreen>

class ScreenHelper
{
public:
    static QString getScreenString(const QScreen &screen);
};

#endif // SCREENHELPER_H
