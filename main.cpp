#include "bi/mode.h"
#include "bi/mastermode.h"
#include "bi/slavemode.h"
#include "bi/testmode.h"

#include <QApplication>
#include <QWindow>
#include <QList>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QDir>

#include "bi/webapimanager.h"
#include "helpers/stringify.h"
#include "helpers/commandlineparserhelper.h"
#include "helpers/signalhelper.h"
#include "helpers/logger.h"
#include "helpers/filenamehelper.h"

#include "settings.h"
#include "bi/constants.h"

/*
    scp 2.jpg pi@172.16.1.17:~/infopanel_pictures
*/

extern Settings settings;
extern Constants constants;


int main(int argc, char *argv[])
{
#if defined (STRINGIFY_H) && defined (STRING) && defined (TARGI)
    QString target = STRING(TARGI);
#else
    auto target=QStringLiteral("ApplicationNameString");
#endif
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName(target);
    QCoreApplication::setApplicationVersion("123");//Buildnumber::_value);
    QCoreApplication::setOrganizationName("LogControl Kft.");
    QCoreApplication::setOrganizationDomain("https://www.logcontrol.hu/");

    SignalHelper::setShutDownSignal(SignalHelper::SIGINT_); // shut down on ctrl-c
    SignalHelper::setShutDownSignal(SignalHelper::SIGTERM_); // shut down on killall

    Logger::Init(Logger::ErrLevel::INFO, Logger::DbgLevel::TRACE, true, true);
    QString user = qgetenv("USER");
    zInfo(QStringLiteral("started ")+target+" as "+user);
    FileNameHelper::Init(QCoreApplication::applicationDirPath());
    bool settings_ok = settings.Load(FileNameHelper::SettingsFileName());
    if(settings_ok){
        zInfo("settings loaded")
    }
    QCommandLineParser parser;

    parser.setApplicationDescription(QStringLiteral("InfoPanel02"));
    parser.addHelpOption();
    parser.addVersionOption();

    const QString OPTION_TEST = QStringLiteral("test");
    const QString OPTION_MASTER = QStringLiteral("master");

    CommandLineParserHelper::addOption(&parser, OPTION_TEST, QStringLiteral("command or command list to test"));
    CommandLineParserHelper::addOptionBool(&parser, OPTION_MASTER, QStringLiteral("set master mode is exists"));

    parser.process(app);

    QString test = parser.value(OPTION_TEST);
    bool hasMasterOption = parser.isSet(OPTION_MASTER);
    bool isMasterMode = hasMasterOption?true:settings.MasterMode();

    zInfo("test: "+test);
    zInfo("isMasterMode: " + QString::number(isMasterMode));

    WebApiManager webApiManager(settings.ApiLocation());

    QDir countDir(settings.CounterDirectory());
    if(!countDir.exists()){
        QDir().mkpath(countDir.absolutePath());
    }

    SlaveMode *slaveMode=nullptr;
    MasterMode *masterMode=nullptr;
    TestMode *testMode=nullptr;
#ifdef RASPBERRY_PI
    if(isMasterMode)
    {
        zInfo("entering MasterMode...");
        masterMode = new MasterMode(&webApiManager);
        masterMode->Start();

        zInfo("Mode: " + QString::number(masterMode->IsMater()));
    }
    else
    {
        zInfo("entering SlaveMode...");
        slaveMode = new SlaveMode(&webApiManager);
        slaveMode->Init();

        zInfo("Mode: " + QString::number(slaveMode->IsMater()));
    }
#else
    zInfo("entering TestMode...");
    constants.SetTestMode(true);
    testMode = new TestMode(&webApiManager);
    bool isStarted = testMode->Start();
#endif
    int e;
    if(isStarted){
        zInfo("app start ok");
        e = app.exec();
    } else{
        zInfo("app start failed");
        e=1;
    }

    zInfo("ExitCode: " + QString::number(e));

    delete(slaveMode);
    delete(masterMode);
    delete(testMode);
    return e;
}


