#ifndef PUBIMAGES_H
#define PUBIMAGES_H

#include "downloadfilemetadata.h"

#include <QList>
#include <QReadWriteLock>
#include <QString>


class PubImages{
private:
    QList<DownloadFileMetaData> _pubImageItems;
    QReadWriteLock _lock;
public:
    PubImages();
    int GetPubImageIx(const QString &name);
    void RemoveAt(int ix);
    QList<DownloadFileMetaData> ExcludeList(const QStringList &names);
    void AddNewItems(const QList<DownloadFileMetaData> &fileList);
};


#endif // PUBIMAGES_H
