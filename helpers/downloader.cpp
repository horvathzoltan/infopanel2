#include <QCoreApplication>
#include <QProcess>

#include "downloader.h"
#include "helpers/logger.h"

bool Downloader::Wget(const QString &url, const QString &filename)
{
    if(url.isEmpty()) return false;
    if(filename.isEmpty()) return false;
    auto out = Execute("wget",{url, "-O", filename});
    return !out.exitCode;
}

Downloader::Output Downloader::Execute(const QString& cmd, const QStringList& args, int timeout){
    QProcess process;
    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LD_LIBRARY_PATH", "/usr/lib"); // workaround - https://bugreports.qt.io/browse/QTBUG-2284
    process.setProcessEnvironment(env);
    static auto path = QCoreApplication::applicationDirPath();
    process.setWorkingDirectory(path);

    process.start(cmd,args);

    if (!process.waitForStarted(-1))
    {
        zInfo("Could not start ");
        return {"","",1};
    }

    bool isFinished = process.waitForFinished(timeout);

    if(!isFinished)
    {
        process.close();
        return {"","",1};
    }

    Output e{process.readAllStandardOutput(),
             process.readAllStandardError(),
             process.exitCode()};
    return e;
}

