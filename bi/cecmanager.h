#ifndef CECMANAGER_H
#define CECMANAGER_H

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTimer>

class CecManager: public QObject
{
    Q_OBJECT

private:
    QTimer* _timer;
    //QMutex _timerMutex;
    bool _On_TimeoutGuard = false;
    QThread* _timerThread;
    bool _enabled;
    bool _verbose;

public:
    CecManager();
    ~CecManager();

    void SetEnabled(bool v){_enabled=v;}
    void SetVerbose(bool v){_verbose=v;}
    void On_Timeout();

signals:
    void PowerOn();
    void PowerOff();
};

#endif // CECMANAGER_H
