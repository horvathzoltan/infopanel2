#ifndef PROCESSREQUEST_H
#define PROCESSREQUEST_H

#include <QString>


class ProcessRequest
{
public:
    bool Process(const QString& request, const QChar& sep = ':');

    bool MasterCmd(const QString& value);
    bool PowCmd(const QString& value);

    bool GetListRequest();
};

#endif // PROCESSREQUEST_H
