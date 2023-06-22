#ifndef TESTMODE_H
#define TESTMODE_H

#include <QObject>
#include "mode.h"
#include "webapimanager.h"

class TestMode : public QObject, public Mode
{
    Q_OBJECT

private:
    WebApiManager *_webApiManager;
public:
    TestMode(WebApiManager* webApiManager, QObject* p = nullptr);
    ~TestMode();
    bool IsInited(){return _webApiManager != nullptr;}

    void Start();
};

#endif // TESTMODE_H
