#include "slideshowmanager.h"
#include "helpers/logger.h"

SlideshowManager::SlideshowManager()
{
    _timer.setSingleShot(true);
    connect(&_timer, &QTimer::timeout, this, &SlideshowManager::On_Timeout);

}

void SlideshowManager::On_Timeout()
{
    zTrace();
}

bool SlideshowManager::Start()
{
    _timer.start();
}

