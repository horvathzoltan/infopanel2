#ifndef ALIVEMANAGER_H
#define ALIVEMANAGER_H

#include <QMutex>
#include <QTimer>
#include "bi/webapimanager.h"

class AliveManager : public QObject
{
    Q_OBJECT

private:
    QTimer _timer;
    QMutex _timerMutex;
    WebApiManager *_webApiManager;

public:
    AliveManager(WebApiManager *webApiManager);

    bool Start();
    void On_Timeout();
signals:
    void NewApplicationDataAvailable();
    void NewApplicationDataRequired();
};

#endif // ALIVEMANAGER_H
