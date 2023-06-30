#include "slideshowmanager.h"
#include "helpers/logger.h"
#include "helpers/textfilehelper.h"

SlideshowManager::SlideshowManager()
{
    _timer.setSingleShot(true);
    connect(&_timer, &QTimer::timeout, this, &SlideshowManager::On_Timeout);
    // todo ha van fájl, felolvasni
    Load();
}

bool SlideshowManager::ReStart()
{
    _currentIx = -1;
    Next();
    return true;
}

void SlideshowManager::SetImages(const QString& serieName, const QList<SlideShowItem>& images)
{    
    bool playing = _timer.isActive();
    if(playing){
        _timer.stop();
    }
    _imagesLock.lockForWrite();
    _images = images;
    _serieName = serieName;
    _imagesLock.unlock();
    Save();
    // todo ki kell írni fájlba, kell a seriename
    if(playing){
        ReStart();
    }
}

bool SlideshowManager::Save(){

    _imagesLock.lockForRead();
    QString txt;
    for(auto&a:_images){
        if(!txt.isEmpty()) txt+='|';
        txt+=a.ToCSV();
    }
    QString msg = "serieName="+_serieName+'\n'+
                  "currentIx="+QString::number(_currentIx)+'\n'+
                  "images="+txt+'\n';
    _imagesLock.unlock();

    bool ok = TextFileHelper::Save(msg, "SlideshowManager.ini", false);

    return ok;
}

bool SlideshowManager::Load(){
    QStringList lines;
    bool ok = TextFileHelper::LoadLines("SlideshowManager.ini", &lines);
    bool retVal = false;
    if(ok && !lines.isEmpty()){
        _imagesLock.lockForWrite();
        for(auto&a:lines){
            bool validLine = !a.isEmpty() && !a.startsWith('#');
            if(validLine){
                int ix = a.indexOf('=');
                if(ix>0){
                    QString key = a.left(ix);
                    QString value = a.mid(ix+1);

                    if(key=="serieName"){

                        _serieName = value;
                    } else if(key =="currentIx"){
                        bool iok;
                        int iv = value.toInt(&iok);
                        if(iok){
                            _currentIx = iv;
                        }
                    } else if(key == "images"){
                        auto ilines = value.split('|');
                        for(auto&iline:ilines){
                            SlideShowItem image;
                            bool ok = SlideShowItem::TryParse(iline, &image);
                            if(ok){
                                _images.append(image);
                            }
                        }

                    }
                }
            }
        }

        _imagesLock.unlock();
        retVal = true;
    }
    return retVal;
}

void SlideshowManager::Next()
{
    _imagesLock.lockForRead();
    int L = _images.length();

    bool valid = L>0;
    if(valid){

        if(_currentIx>-1){
            zInfo("Prev:"+QString::number(_currentIx));
        }

        if(_currentIx==-1){
            _currentIx=0;
        } else if(_currentIx>=L) {
            _currentIx=0;
        }
        int ix0 = _currentIx;
        while(++_currentIx!=ix0){
            if(_currentIx>=L)
                _currentIx=0;

            auto currentImage = _images[_currentIx];
            bool validImage = currentImage.IsValid();

            if(validImage){
                _timer.setInterval(currentImage.IntervalMs());
                _timer.start();
                emit ChangeImage();
                break;
            }
        }
        if(_currentIx==ix0){
            emit HideImage();
        }
    }
    _imagesLock.unlock();
}

QString SlideshowManager::GetCurrentImageName()
{
    bool valid = _currentIx>=0 && _currentIx<_images.length();
    QString retVal;
    if(valid){
        _imagesLock.lockForRead();
        retVal =  _images[_currentIx].filename;
        _imagesLock.unlock();
    }
    return retVal;
}

int SlideshowManager::GetCurrentImageTime()
{
    bool valid = _currentIx>=0 && _currentIx<_images.length();
    int retVal=-1;
    if(valid){
        _imagesLock.lockForRead();
        retVal =  _images[_currentIx].timeout;
        _imagesLock.unlock();
    }
    return retVal;
}

int SlideshowManager::ImagesLength()
{
    bool valid = _currentIx>=0 && _currentIx<_images.length();
    int retVal=-1;
    if(valid){
        _imagesLock.lockForRead();
        retVal =  _images.length();
        _imagesLock.unlock();
    }
    return retVal;
}

void SlideshowManager::On_Timeout()
{
    Next();
}

