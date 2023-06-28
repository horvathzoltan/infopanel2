#ifndef TESTMODE_H
#define TESTMODE_H

#include <QList>
#include <QObject>
#include "bi/downloadmanager.h"
#include "mode.h"
#include "webapimanager.h"

class TestMode : public QObject, public Mode
{
    Q_OBJECT

private:
    WebApiManager *_webApiManager;
    DownloadManager _downloadManager;

    QString _lastApplicationDataVersion_Local;
    QString _lastApplicationDataVersion_Remote;
    QString _lastApplicationVersion;

    const Application *_application;    

public:
    TestMode(WebApiManager* webApiManager, QObject* p = nullptr);
    ~TestMode();
    bool IsInited(){return _webApiManager != nullptr;}

    bool Start();
};

#endif // TESTMODE_H
