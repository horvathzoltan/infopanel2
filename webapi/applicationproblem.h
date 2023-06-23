#ifndef APPLICATIONPROBLEM_H
#define APPLICATIONPROBLEM_H

#include <QString>
#include <QJsonObject>

class ApplicationProblem
{
private:
    QString type;
    QString title;
    int status;
    QString detail;
    QString instance;
    QMap<QString, QString> _fields;
public:
    ApplicationProblem();

    static ApplicationProblem JsonParse(const QJsonObject& o);

    const QString& Title(){return title;}
};

#endif // APPLICATIONPROBLEM_H
