#ifndef SLIDESHOWITEM_H
#define SLIDESHOWITEM_H

#include <QString>
#include <QUuid>

class SlideShowItem
{
public:
    QString filename;
    int timeout;
    QUuid id;
public:
    bool IsValid();
    int IntervalMs(){return timeout*1000;}
    QString ToCSV();
    static bool TryParse(const QString& txt, SlideShowItem *p);
};

#endif // SLIDESHOWITEM_H
