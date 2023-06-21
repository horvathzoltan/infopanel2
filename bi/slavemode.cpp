#include "slavemode.h"
#include <QScreen>
#include <QApplication>


#include "helpers/logger.h"

SlaveMode::SlaveMode() : Mode(false)
{

}

SlaveMode::~SlaveMode()
{
    delete(_w1);
    delete(_w2);
    zInfo("leaving SlaveMode...");
}

void SlaveMode::Init()
{
    QList<QScreen*> screens = qApp->screens();
    zInfo("screens_length:"+QString::number(screens.length()));
    foreach(QScreen* a,screens)
    {
        zInfo("screen_name:"+a->name());
    }

    if(screens.length()>=1)
    {
        _w1 = new Form3();
/*
        QScreen *screen = screens[0];
        _w1->move(screen->geometry().x(), screen->geometry().y());
        _w1->resize(screen->geometry().width(), screen->geometry().height());
*/
        //_w1->showFullScreen();
        _w1->show();
    }

    if(screens.length()>=2){
        _w2 = new Frame2();
/*
        QScreen *screen = screens[1];
        _w2->move(screen->geometry().x(), screen->geometry().y());
        _w2->resize(screen->geometry().width(), screen->geometry().height());
*/
        //_w2->showFullScreen();
        _w2->show();
    }
}
