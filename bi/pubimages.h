#ifndef PUBIMAGES_H
#define PUBIMAGES_H

#include "downloadfilemetadata.h"

#include <QList>
#include <QReadWriteLock>
#include <QString>


class DownloadFiles{
private:
    QList<DownloadFileMetaData> _pubImageItems;
    QReadWriteLock _lock;
public:
    DownloadFiles();
    int GetPubImageIx(const QString &name);
    void RemoveAt(int ix);
    QList<DownloadFileMetaData> ExcludeList(const QStringList &names);
    void AddNewItems(const QList<DownloadFileMetaData> &fileList);
    void SetItemLength(int ix, qint64 length);
    qint64 GetItemLength(int ix);

    int ItemCount(){return _pubImageItems.count();}
};


#endif // PUBIMAGES_H
