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
    return filename+';'+QString::number(timeout)+';'+id.toString(QUuid::WithoutBraces);
}

bool SlideShowItem::TryParse(const QString& txt, SlideShowItem *p){
    bool valid = !txt.isEmpty() && p!=nullptr;
    bool retVal = false;
    if(valid){
        QStringList lines = txt.split(';', Qt::SkipEmptyParts);
        if(lines.length()>=3){
            p->filename = lines[0];
            bool iok;
            int iv= lines[1].toInt(&iok);
            if(iok){
                p->timeout=iv;
            }
            QUuid iq = QUuid::fromString(lines[2]);
            if(!iq.isNull()){
                p->id=iq;
            }
            retVal = true;
        }
    }
    return retVal;
}
