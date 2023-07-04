#ifndef CECMANAGER_H
#define CECMANAGER_H

#include <QMutex>
#include <QObject>
#include <QTimer>

class CecManager: public QObject
{
    Q_OBJECT

private:
    QTimer _timer;
    QMutex _timerMutex;
public:
    CecManager();

    bool Start();
    bool Stop();
    void On_Timeout();
};

#endif // CECMANAGER_H
