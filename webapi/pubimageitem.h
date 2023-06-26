#ifndef PUBIMAGEITEM_H
#define PUBIMAGEITEM_H

#include <QJsonObject>
#include <QUuid>

class PubImageItem
{
public:
    /// <summary>
    /// Image guid
    /// </summary>
    QUuid id;// { get; set; }

    /// <summary>
    /// Download url of the image
    /// </summary>
    QString imageUrl;// { get; set; } = string.Empty;

    /// <summary>
    /// Display time on the device in seconds
    /// </summary>
    int displayTimeSconds=10;// { get; set; } = 10;

public:
    PubImageItem();

    static PubImageItem JsonParse(const QJsonObject &jsonObject);
};
#endif // PUBIMAGEITEM_H
