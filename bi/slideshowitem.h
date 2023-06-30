#ifndef SLIDESHOWITEM_H
#define SLIDESHOWITEM_H

#include <QString>

class SlideShowItem
{
public:
    QString filename;
    int timeout;

public:
    bool IsValid();
    int IntervalMs(){return timeout*1000;}
    QString ToCSV();
    static bool TryParse(const QString& txt, SlideShowItem *p);
};

#endif // SLIDESHOWITEM_H
