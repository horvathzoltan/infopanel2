#include "slavemode.h"
#include <QScreen>
#include <QApplication>

#include "helpers/logger.h"
#include "processrequest.h"
#include "settings.h"

extern Settings settings;

SlaveMode::SlaveMode(WebApiManager* webApiManager,
                     QObject*p): QObject(p), Mode(false)
{
    _webApiManager = webApiManager;
}

SlaveMode::~SlaveMode()
{
    delete(_w1);
    delete(_w2);
    zInfo("leaving SlaveMode...");
}

void SlaveMode::Init()
{
    _tcpSocketServer.SetmRequestProcessor(&ProcessRequest::Process, _processRequest);
    auto slavePort = settings.SlavePort();
    _tcpSocketServer.Listen(QHostAddress::Any, slavePort);

    QList<QScreen*> screens = qApp->screens();
    zInfo("screens_length:"+QString::number(screens.length()));

    if(screens.length()>0){
        for(QScreen* a:screens)
        {
            zInfo("screen_name:"+a->name());
        }

        bool isFullScreen = settings.SlaveFullSize();
        if(screens.length()>=1){
            _w1 = new Form3();
            if(isFullScreen){
                QScreen *screen = screens[0];
                _w1->move(screen->geometry().x(), screen->geometry().y());
                _w1->resize(screen->geometry().width(), screen->geometry().height());
                _w1->showFullScreen();
            } else {
                _w1->show();
            }
        }

        if(screens.length()>=2){
            _w2 = new Frame2();
            if(isFullScreen){
                QScreen *screen = screens[1];
                _w2->move(screen->geometry().x(), screen->geometry().y());
                _w2->resize(screen->geometry().width(), screen->geometry().height());
                _w2->showFullScreen();
            } else {
                _w2->show();
            }
        }
    }
}
