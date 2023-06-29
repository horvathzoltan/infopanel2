#include "httpresponse.h"

const QMap<HttpResponse::Status::Codes, QString> HttpResponse::Status::_statusPhrases {
    {Continue, QStringLiteral("Continue")},
    {SwitchingProtocols, QStringLiteral("Switching Protocols")},

    {OK, QStringLiteral("OK")},
    {Created, QStringLiteral("Created")},
    {Accepted, QStringLiteral("Accepted")},
    {NonAuthoritativeInformation, QStringLiteral("Non-Authoritative Information")},
    {NoContent, QStringLiteral("No Content")},
    {ResetContent, QStringLiteral("Reset Content")},
    {PartialContent, QStringLiteral("Partial Content")},
    {MultipleChoices, QStringLiteral("Multiple Choices")},
    {MovedPermanently, QStringLiteral("Moved Permanently")},
    {Found, QStringLiteral("Found")},
    {SeeOther, QStringLiteral("See Other")},
    {NotModified, QStringLiteral("Not Modified")},
    {UseProxy, QStringLiteral("Use Proxy")},
    {TemporaryRedirect, QStringLiteral("Temporary Redirect")},

    {BadRequest, QStringLiteral("Bad Request")},
    {Unauthorized, QStringLiteral("Unauthorized")},
    {PaymentRequired, QStringLiteral("Payment Required")},
    {Forbidden, QStringLiteral("Forbidden")},
    {NotFound, QStringLiteral("Not Found")},
    {MethodNotAllowed, QStringLiteral("Method Not Allowed")},
    {NotAcceptable, QStringLiteral("Not Acceptable")},
    {ProxyAuthenticationRequired, QStringLiteral("Proxy Authentication Required")},
    {RequestTimeout, QStringLiteral("Request Time-out")},
    {Conflict, QStringLiteral("Conflict")},
    {Gone, QStringLiteral("Gone")},
    {LengthRequired, QStringLiteral("Length Required")},
    {PreconditionFailed, QStringLiteral("Precondition Failed")},
    {RequestEntityTooLarge, QStringLiteral("Request Entity Too Large")},
    {RequestURItooLarge, QStringLiteral("Request-URI Too Large")},
    {UnsupportedMediaType, QStringLiteral("Unsupported Media Type")},
    {RequestedRangeNotSatisfiable, QStringLiteral("Requested range not satisfiable")},
    {ExpectationFailed, QStringLiteral("Expectation Failed")},

    {InternalServerError, QStringLiteral("Internal Server Error")},
    {NotImplemented, QStringLiteral("Not Implemented")},
    {BadGateway, QStringLiteral("Bad Gateway")},
    {ServiceUnavailable, QStringLiteral("Service Unavailable")},
    {GatewayTimeout, QStringLiteral("Gateway Time-out")},
    {HTTPversionNotSupported, QStringLiteral("HTTP Version not supported")}
};



HttpResponse::HttpResponse()
{

}

HttpResponse HttpResponse::Parse(const QString &str)
{
    bool valid = !str.isEmpty();
    HttpResponse r;
    if(valid){
        int ix1 = str.indexOf("\r\n\r\n");

        QStringList lines;
        if(ix1>=0){
            r._body = str.mid(ix1+4);
            lines = str.left(ix1).split("\r\n");
        }
        else
        {
            lines = str.split("\r\n");
        }

        if(lines.length()>=1){
            r._status = Status::Parse(lines[0]);
            if(lines.length()>=2){
                for(int i=1;i<lines.length();i++){
                    QPair<QString, QString> p;
                    bool ok = TryParseHeaderLine(lines[i], &p);
                    if(ok){
                        r._headerFields.insert(p.first, p.second);
                    }
                }
            }
        }
    }

    return r;
}

qint64 HttpResponse::ContentLength()
{
    const QString key = QStringLiteral("content-length");
    qint64 retVal = -1;
    if(_headerFields.contains(key)){
        QString v = _headerFields.value(key);
        bool ok;
        qint64 l = v.toLongLong(&ok);
        if(ok){
            retVal = l;
        }
    }
    return retVal;
}

bool HttpResponse::IsContentType(const QString &c)
{
    bool retVal = false;
    const QString key = QStringLiteral("content-type");
    if(_headerFields.contains(key)){
        auto v = _headerFields.value(key);
        int ix = v.indexOf(';');
        QString value = (ix>=0)?c.left(ix):c;

        bool equals = value.compare(c, Qt::CaseInsensitive) == 0;
        if(equals){
            retVal = true;
        }
    }
    return retVal;
}

bool HttpResponse::TryParseHeaderLine(const QString &str, QPair<QString, QString> *p )
{
    bool retVal = false;
    bool valid = !str.isEmpty() && p!= nullptr;
    if(valid){
        int ix = str.indexOf(':');
        if(ix>1){
            p->first = str.left(ix).trimmed().toLower();
            p->second = str.mid(ix+1).trimmed();
            retVal = true;
        }
    }
    return retVal;
}

HttpResponse::Status HttpResponse::Status::Parse(const QString &str)
{
    bool valid = !str.isEmpty();
    Status s;
    if(valid){
        auto tokens=str.split(' ');
        if(tokens.length()>=2){
            s.HTTP_Version=tokens[0];
            s.statusCode=tokens[1].toInt();
            if(tokens.length()>=3){
                s.reasonPhrase=tokens[2];
            }
        }
    }
    return s;
}

