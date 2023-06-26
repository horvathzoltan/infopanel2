#ifndef PUBAPPLICATIONDATA_H
#define PUBAPPLICATIONDATA_H

#include "pubimageitem.h"

#include <QJsonObject>
#include <QList>
#include <QString>

class PubApplicationData
{
public:

    /// <summary>
    /// Application data version number: if there are new data for the applicaiton, this will be changed
    /// </summary>
    QString applicationDataVersion;// { get; set; } = string.Empty;

        /// <summary>
        /// This list contains the images and display times
        /// </summary>
    QList<PubImageItem> pubImageItems;// { get; set; } = new List<PubImageItem>();

public:
    PubApplicationData();

    static PubApplicationData JsonParse(const QJsonObject& o);
};

#endif // PUBAPPLICATIONDATA_H
