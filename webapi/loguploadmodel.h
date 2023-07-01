#ifndef LOGUPLOADMODEL_H
#define LOGUPLOADMODEL_H

#include <QDateTime>
#include <QUuid>

class LogUploadModel
{
    /// <summary>
    /// Image guid
    /// </summary>
    QUuid id;// { get; set; }

    /// <summary>
    /// The date and time when the image has been displayed
    /// </summary>
    QDateTime displayTimeStamp;// { get; set; }

    /// <summary>
    /// The display duration time in seconds
    /// </summary>
    int seconds;// { get; set; }

public:
    LogUploadModel();

    QString ToJson() const;

    static LogUploadModel Parse(const QString& txt);
    static QList<LogUploadModel> ParseList(const QString& txt);
};

#endif // LOGUPLOADMODEL_H
