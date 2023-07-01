#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QMutex>
#include <QObject>
#include <QTimer>


class LogManager: public QObject
{
    Q_OBJECT

private:
    QTimer _timer;
    QMutex _timerMutex;

public:
    LogManager();

    bool Start();
    bool Stop();
    void On_Timeout();
};

#endif // LOGMANAGER_H
