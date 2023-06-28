#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QString>
#include <QMap>

class HttpResponse
{
private:
    QMap<QString, QString> _headerFields;
    QString _body;

    struct Status{
    public:
        enum Codes: int {
            //Informational
            Continue=100,
            SwitchingProtocols=101,
            //Successful
            OK=200,
            Created=201,
            Accepted=202,
            NonAuthoritativeInformation=203,
            NoContent=204,
            ResetContent=205,
            PartialContent=206,
            //Redirection;
            MultipleChoices=300,
            MovedPermanently=301,
            Found=302,
            SeeOther=303,
            NotModified=304,
            UseProxy=305,
            TemporaryRedirect=307,
            //Client Error
            BadRequest=400,
            Unauthorized=401,
            PaymentRequired=402,
            Forbidden=403,
            NotFound=404,
            MethodNotAllowed=405,
            NotAcceptable=406,
            ProxyAuthenticationRequired=407,
            RequestTimeout=408,
            Conflict=409,
            Gone=410,
            LengthRequired=411,
            PreconditionFailed=412,
            RequestEntityTooLarge=413,
            RequestURItooLarge=414,
            UnsupportedMediaType=415,
            RequestedRangeNotSatisfiable=416,
            ExpectationFailed=417,
            //Server Error
            InternalServerError=500,
            NotImplemented=501,
            BadGateway=502,
            ServiceUnavailable=503,
            GatewayTimeout=504,
            HTTPversionNotSupported=505
        };

        static const QMap<Codes, QString> _statusPhrases;

        QString HTTP_Version;
        int statusCode;
        QString reasonPhrase;

        static Status Parse(const QString& str);
    };

    Status _status;

    static bool TryParseHeaderLine(const QString &str, QPair<QString, QString> *p );

public:
    HttpResponse();
    static HttpResponse Parse(const QString& str);

    const QString& Body(){return _body;}

    int StatusCode(){return _status.statusCode;}
    qint64 ContentLength();
    //https://www.rfc-editor.org/rfc/rfc9110.html#name-overview-of-status-codes
    bool IsSuccessful(){return 200<=_status.statusCode && _status.statusCode<=299;}
    //https://www.rfc-editor.org/rfc/rfc9110.html#name-client-error-4xx
    bool IsClientError(){return 400<=_status.statusCode && _status.statusCode<=499;}
    bool IsServerError(){return 500<=_status.statusCode && _status.statusCode<=599;}

    bool IsContentType(const QString& c);
};

#endif // HTTPRESPONSE_H
