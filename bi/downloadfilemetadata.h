#ifndef DOWNLOADFILEMETADATA_H
#define DOWNLOADFILEMETADATA_H

#include <QString>

struct DownloadFileMetaData{
    QString filename;
    qint64 size;
    QString url;
};

#endif // DOWNLOADFILEMETADATA_H
