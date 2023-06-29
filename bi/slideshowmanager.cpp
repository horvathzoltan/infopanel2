#include "slideshowmanager.h"
#include "helpers/logger.h"

SlideshowManager::SlideshowManager()
{
    _timer.setSingleShot(true);
    connect(&_timer, &QTimer::timeout, this, &SlideshowManager::On_Timeout);
}

bool SlideshowManager::Start()
{
    _currentIx = -1;
    Next();
    return true;
}

void SlideshowManager::SetImages(QList<SlideShowItem> images)
{
    _images = images;
}

void SlideshowManager::Next()
{
    if(_currentIx>-1){
        zInfo("Prev:%1"+QString::number(_currentIx));
    }
    if(++_currentIx>=_images.length())
        _currentIx=0;
    emit ChangeImage();
    _timer.setInterval(_images[_currentIx].timeout*1000);
    _timer.start();
}

QString SlideshowManager::GetCurrentImageName()
{
    return _images[_currentIx].filename;
}

void SlideshowManager::On_Timeout()
{
    zTrace();
    Next();
}

