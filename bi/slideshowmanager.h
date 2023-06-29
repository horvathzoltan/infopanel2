#ifndef SLIDESHOWMANAGER_H
#define SLIDESHOWMANAGER_H

#include <QTimer>

class SlideshowManager : public QObject
{
    Q_OBJECT

private:
    QTimer _timer;
public:
    SlideshowManager();
    void On_Timeout();
    bool Start();
};

#endif // SLIDESHOWMANAGER_H
