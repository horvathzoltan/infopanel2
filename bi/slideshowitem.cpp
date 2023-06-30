#include "slideshowitem.h"
#include <QFile>


bool SlideShowItem::IsValid()
{
    bool fileExists = QFile::exists(filename);
    bool valid = timeout>5 && timeout < 60*60*24
                 && fileExists;
    return valid;
}

QString SlideShowItem::ToCSV()
{
    return filename+';'+QString::number(timeout);
}

bool SlideShowItem::TryParse(const QString& txt, SlideShowItem *p){
    bool valid = !txt.isEmpty() && p!=nullptr;
    bool retVal = false;
    if(valid){
        QStringList lines = txt.split(';', Qt::SkipEmptyParts);
        if(lines.length()>=2){
            p->filename = lines[0];
            bool iok;
            int iv= lines[1].toInt(&iok);
            if(iok){
                p->timeout=iv;
            }
            retVal = true;
        }
    }
    return retVal;
}
