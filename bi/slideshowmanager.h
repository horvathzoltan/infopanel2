#ifndef SLIDESHOWMANAGER_H
#define SLIDESHOWMANAGER_H

#include "slideshowitem.h"

#include <QTimer>

class SlideshowManager : public QObject
{
    Q_OBJECT

private:
    QTimer _timer;
    QList<SlideShowItem> _images;
    int _currentIx;

public:
    SlideshowManager();
    void On_Timeout();
    bool Start();
    void SetImages(QList<SlideShowItem> images);
    void Next();
    QString GetCurrentImageName();
signals:
    void ChangeImage();

};

#endif // SLIDESHOWMANAGER_H
