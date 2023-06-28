#include "pubimages.h"

PubImages::PubImages()
{

}

void PubImages::RemoveAt(int ix)
{
    _lock.lockForWrite();
    _pubImageItems.removeAt(ix);
    _lock.unlock();
}

QList<DownloadFileMetaData> PubImages::ExcludeList(const QStringList &filenamelist)
{
    QList<DownloadFileMetaData> e;
    _lock.lockForRead();
    for(auto&a:_pubImageItems){
        if(!filenamelist.contains(a.filename)){
            e.append(a);
        }
    }
    _lock.unlock();
    return e;
}

int PubImages::GetPubImageIx(const QString& name){

    int ix = -1;
    _lock.lockForRead();
    int L = _pubImageItems.count();
    for (int i=0;i<L;i++) {
        if(_pubImageItems[i].filename==name){
            ix=i;
            break;
        }
    }
    _lock.unlock();
    return ix;
}

void PubImages::AddNewItems(const QList<DownloadFileMetaData> &fileList)
{
    _lock.lockForWrite();
    _pubImageItems.append(fileList);
    _lock.unlock();
}

void PubImages::SetLength(int ix, qint64 length)
{
    bool valid = ix>-1 && ix<_pubImageItems.length();
    if(valid){
        _pubImageItems[ix].size=length;
    }
}

qint64 PubImages::GetLength(int ix)
{
    qint64 retVal=-1;
    bool valid = ix>-1 && ix<_pubImageItems.length();
    if(valid){
        retVal=_pubImageItems[ix].size;
    }
    return retVal;
}
