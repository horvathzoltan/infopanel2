#include "slideshowmanager.h"
#include "helpers/logger.h"
#include "bi/filenamehelper.h"
#include "helpers/textfilehelper.h"

SlideshowManager::SlideshowManager()
{
    _timer.setSingleShot(true);
    connect(&_timer, &QTimer::timeout, this, &SlideshowManager::On_Timeout);
    Load();
    _remainingIx = -1;
    _remainingTime = -1;
}

bool SlideshowManager::ReStart()
{
    if(_remainingIx==-1&&_remainingTime==-1){
        LoadState();
        DelState();
    }

    _currentIx = -1;
    Next();
    return true;
}

bool SlideshowManager::Stop()
{
    if(_timer.isActive()){                
        _remainingTime = _timer.remainingTime(); // millis
        _timer.stop();
        _remainingIx = _currentIx;
        SaveState();
    }
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

    // todo ki kell írni fájlba, kell a seriename
    if(playing){
        ReStart();
    }
}

void SlideshowManager::SaveImages(){
    Save();
    _remainingIx = -1;
    _remainingTime = -1;
    DelState();
}

bool SlideshowManager::Save(){
    bool retVal = false;

    _imagesLock.lockForRead();
    QString txt;
    for(auto&a:_images){
        if(!txt.isEmpty()) txt+='|';
        txt+=a.ToCSV();
    }
    QString content = "serieName="+_serieName+'\n'+
                  "currentIx="+QString::number(_currentIx)+'\n'+
                  "images="+txt+'\n';
    _imagesLock.unlock();

    QString fn = FileNameHelper::GetSlideShowFileName();
    bool fileNameOk = !fn.isEmpty();
    if(fileNameOk){
        bool ok = TextFileHelper::Save(content, fn, false);
        if(ok){
            retVal = true;
        }
    }

    return retVal;
}

bool SlideshowManager::Load(){    
    QString fn = FileNameHelper::GetSlideShowFileName();
    bool fileNameOk = !fn.isEmpty();
    bool retVal = false;
    if(fileNameOk){
        QStringList lines;
        bool ok = TextFileHelper::LoadLines(fn, &lines);
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
    }
    return retVal;
}

// _currentIx-től kéne indítani, de ha van remaining, akkor azt kellene folytatni

void SlideshowManager::Next()
{
    _imagesLock.lockForRead();
    int L = _images.length();

    bool valid = L>0;
    if(valid){

        if(_currentIx>-1){
            zInfo("Prev:"+QString::number(_currentIx));
        }
        if(_remainingIx!=-1){
            _currentIx = _remainingIx;
        } else{
            _currentIx++;
        }
        /*        if(_currentIx==-1){
            _currentIx=0;
        } else */
        if(_currentIx>=L) {
            _currentIx=0;
        }
        int ix0 = _currentIx;
        bool notFound = true;
        while(true){
            auto currentImage = _images[_currentIx];
            bool validImage = currentImage.IsValid();
            int t;
            if(_remainingTime!=-1){
                t = _remainingTime;
                _remainingIx=-1;
                _remainingTime=-1;
            }else {
                t = currentImage.IntervalMs();
            }
            if(validImage){
                _timer.setInterval(t);
                _timer.start();
                emit ChangeImage();
                notFound = false;
                break;
            }
            _currentIx++;
            if(_currentIx==ix0){ // vagy megtaláltuk, vagy körbeértünk
                break;
            }
            if(_currentIx>=L){
                _currentIx=0;
            }
        }
        if(notFound){ // ha körbeértünk, nem volt meg a kép
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

QUuid SlideshowManager::GetCurrentId()
{
    bool valid = _currentIx>=0 && _currentIx<_images.length();
    QUuid retVal;
    if(valid){
        _imagesLock.lockForRead();
        retVal = _images[_currentIx].id;
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


bool SlideshowManager::SaveState(){
    bool retVal = false;
    QString fn = FileNameHelper::GetSlideShowStateFileName();
    bool fileNameOk = !fn.isEmpty();
    if(fileNameOk){
        QString content = "remainingTime="+QString::number(_remainingTime)+'\n'+
                          "remainingIx="+QString::number(_remainingIx)+'\n';

        bool ok = TextFileHelper::Save(content, fn, false);
        if(ok){
            retVal = true;
        }
    }
    return retVal;
}

bool SlideshowManager::LoadState(){
    bool retVal = false;
    QString fn = FileNameHelper::GetSlideShowStateFileName();
    bool fileNameOk = !fn.isEmpty();
    if(fileNameOk){
        QStringList lines;
        bool ok = TextFileHelper::LoadLines(fn, &lines);
        if(ok && !lines.isEmpty()){
            //_imagesLock.lockForWrite();
            for(auto&a:lines){
                bool validLine = !a.isEmpty() && !a.startsWith('#');
                if(validLine){
                    int ix = a.indexOf('=');
                    if(ix>0){
                        QString key = a.left(ix);
                        QString value = a.mid(ix+1);

                        if(key=="remainingTime"){
                            bool iok;
                            int iv = value.toInt(&iok);
                            if(iok){
                                _remainingTime = iv;
                            }
                        } else if(key =="remainingIx"){
                            bool iok;
                            int iv = value.toInt(&iok);
                            if(iok){
                                _remainingIx = iv;
                            }
                        }
                    }
                }
            }
            retVal = true;
            //_imagesLock.unlock();
        }
    }
    return retVal;
}

bool SlideshowManager::DelState(){
    QString fn = FileNameHelper::GetSlideShowStateFileName();
    FileNameHelper::DeleteFile(fn);
    return true;
}
