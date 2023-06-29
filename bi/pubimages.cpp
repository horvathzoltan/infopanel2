#include "pubimages.h"

DownloadFiles::DownloadFiles()
{

}

void DownloadFiles::RemoveAt(int ix)
{
    _lock.lockForWrite();
    _pubImageItems.removeAt(ix);
    _lock.unlock();
}

QList<DownloadFileMetaData> DownloadFiles::ExcludeList(const QStringList &filenamelist)
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

int DownloadFiles::GetPubImageIx(const QString& name){

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

void DownloadFiles::AddNewItems(const QList<DownloadFileMetaData> &fileList)
{
    _lock.lockForWrite();
    _pubImageItems.append(fileList);
    _lock.unlock();
}

void DownloadFiles::SetLength(int ix, qint64 length)
{
    bool valid = ix>-1 && ix<_pubImageItems.length();
    if(valid){
        _pubImageItems[ix].size=length;
    }
}

qint64 DownloadFiles::GetLength(int ix)
{
    qint64 retVal=-1;
    bool valid = ix>-1 && ix<_pubImageItems.length();
    if(valid){
        retVal=_pubImageItems[ix].size;
    }
    return retVal;
}
