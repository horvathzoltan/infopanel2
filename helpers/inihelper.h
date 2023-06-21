#ifndef INIHELPER_H
#define INIHELPER_H

#include <QString>
#include <QMap>
#include <QStringList>

class IniHelper
{
public:
public:
    //static bool Load(const QString &fn, QStringList *lines);
    static QMap<QString, QString> Parse(const QStringList& lines,const QChar& sep='=');
    static bool TryGetValue(QMap<QString, QString>m, const QString& key, QString *value);
    //static QString ToString(const QMap<QString, QString>&, const QString&);

};

#endif // INIHELPER_H
