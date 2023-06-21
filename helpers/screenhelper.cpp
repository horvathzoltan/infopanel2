#include "screenhelper.h"



QString ScreenHelper::getScreenString(const QScreen &screen)
{
    QSize screenSize = screen.size();

    QString msg = QStringLiteral("%1@%4:%2 %3").
                  arg(screen.name()).
                  arg(screen.manufacturer()).
                  arg(screen.model()).
                  arg(
        QString::number(screenSize.width())+'x'+
        QString::number(screenSize.height())
                                                                                                                     );

    return msg;
}
