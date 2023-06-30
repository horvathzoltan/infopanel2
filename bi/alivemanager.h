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
    QString _applicationDataVersion;
    QString _applicationVersion;
public:
    AliveManager(WebApiManager *webApiManager);

    bool Start();
    void On_Timeout();
    bool Stop();
    void SetApplicationDataVersion(const QString& v){_applicationDataVersion = v;}
    void SetApplicationVersion(const QString& v){_applicationVersion = v;}
signals:
    void NewApplicationDataAvailable();
    void NewApplicationDataRequired();
    void NewApplicationAvailable();
    void NewApplicationRequired();
    void Alive();
};

#endif // ALIVEMANAGER_H
