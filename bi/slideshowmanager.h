#ifndef SLIDESHOWMANAGER_H
#define SLIDESHOWMANAGER_H

#include "slideshowitem.h"

#include <QMutex>
#include <QReadWriteLock>
#include <QTimer>

class SlideshowManager : public QObject
{
    Q_OBJECT

private:   
    QTimer _timer;
    QList<SlideShowItem> _images;
    QReadWriteLock _imagesLock;
    int _currentIx;
    QString _serieName;
    QString _downloadDirectory;

public:
    SlideshowManager();
    void On_Timeout();
    bool ReStart();
    bool Stop();
    bool IsStarted(){return _timer.isActive(); };
    void SetImages(const QString& fn, const QList<SlideShowItem>& images);
    void Next();
    QString GetCurrentImageName();
    int GetCurrentImageTime();
    QUuid GetCurrentId();
    QString GetSerieName(){return _serieName;};    
    int ImagesLength();
    bool Save();
    bool Load();
    QString GetFn();
signals:
    void ChangeImage();
    void HideImage();

};

#endif // SLIDESHOWMANAGER_H
