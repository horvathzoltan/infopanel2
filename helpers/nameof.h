#ifndef NAMEOF_H
#define NAMEOF_H

#include <QRegularExpression>
#include <QString>

//#define nameof(x) NameOf::_nameof<0>(#x, sizeof(x))
#define STRINGIFY_R(msg) #msg
#define nameof(x) NameOf::_nameof_ulong(#x, sizeof(x))
#define nameof_fn(x) NameOf::_nameof_fn(#x, (void*)x)

class NameOf{
private:
    static QString NameOf_private(const QString &x);
public:
    //template<int a>
    static QString _nameof_fn(const char *y, void *);

    //template<int a>
    static QString _nameof(const char *y, std::size_t);

    //template<int a>
    static QString _nameof_ulong(char const *y, unsigned long);
};

#endif // NAMEOF_H
