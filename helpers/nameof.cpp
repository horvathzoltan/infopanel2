#include "helpers/nameof.h"

QString NameOf::NameOf_private(const QString& x){
    static const QRegularExpression refn(QStringLiteral(R"((?:::|->|\.)?([\w]+)\(\)$)"));
    static const QRegularExpression re(QStringLiteral(R"((?:->|\.|::)?([_a-zA-Z]\w*)$)"));
    QRegularExpressionMatch m;

    if(x.endsWith(QStringLiteral("()"))) m = refn.match(x);
    else m = re.match(x);

    if (!m.hasMatch()) return QStringLiteral("A bad expression in nameof(%1)").arg(x);

    auto name = m.captured(m.lastCapturedIndex());
    return name;
}

//template<int a>
QString NameOf::_nameof_fn(const char* y, void*)
{
    return NameOf_private(QString(y));
}

//template<int a>
QString NameOf::_nameof(const char* y, std::size_t)
{
    return NameOf_private(QString(y));
}

//template<int a>
QString NameOf::_nameof_ulong(char const *y, unsigned long)
{
    return NameOf_private(QString(y));
}
