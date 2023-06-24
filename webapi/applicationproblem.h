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
    QMap<QString, QVariant> _fields;
public:
    ApplicationProblem();

    static ApplicationProblem JsonParse(const QJsonObject& o);

    QString Title(){return title;}

    QStringList GetErrors();
    static QStringList ErrorHandler(const QString &err);
};

#endif // APPLICATIONPROBLEM_H
