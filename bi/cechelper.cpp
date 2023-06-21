#include "cechelper.h"

#include "helpers/logger.h"
#include "helpers/processhelper.h"

#include <QProcess>
#include <QApplication>


// /bin/sh -c echo "pow 0" | cec-client -s -d 2 /dev/cec1
int CECHelper::GetPowerState()
{
    const QString CMD = QStringLiteral("echo \"pow 0\" | cec-client -s -d 2 /dev/cec1");
    auto o = ProcessHelper::ShellExecute(CMD);
    if(!o.stdErr.isEmpty()) return -1;

    auto value = GetValue(o.stdOut, QStringLiteral("power status"), ':');

    zInfo("value: "+value);
    zInfo("time: "+QString::number(o.elapsedMillis));

    if(value == "standby") return 0;
    if(value == "on") return 1;
    return -1;
}


QString CECHelper::GetValue(const QString& str, const QString& token,const QChar& sep){

    int token_length = token.length();

    QStringList lines = str.split('\n');
    for(auto&line:lines){
        if(!line.startsWith(token)) continue;
        int ix = line.indexOf(sep, token_length, Qt::CaseInsensitive );
        if(ix==-1) continue;
        return line.mid(ix+1).trimmed();
    }
    return {};
}


// echo "pow 0" | cec-client -s -d 2 /dev/cec1

bool CECHelper::GetPowerState_2()
{
    //QString cmd1 = QStringLiteral("echo 'pow 0' | cec-client -s -d 2 /dev/cec1");
    //ProcessHelper::Model m1 = ProcessHelper::Model::Parse(QStringLiteral("echo 'pow 0'"));
    //ProcessHelper::Model m2 = ProcessHelper::Model::Parse(QStringLiteral("cec-client -s -d 2 /dev/cec1"));

    //    ProcessHelper::Model m1 = {.cmd="echo",
    //                               .args={"\"pow 0\""},
    //                               .timeout=-1};
    //    ProcessHelper::Model m2 = {.cmd="cec-client",
    //                               .args={"-s","-d", "2", "/dev/cec1"},
    //                               .timeout=-1};

    //    QList<ProcessHelper::Model> m = {m1,m2};

    //    ProcessHelper::Output out = ProcessHelper::ExecutePiped(m);
    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();


    env.insert("LD_LIBRARY_PATH", "/usr/lib"); // workaround - https://bugreports.qt.io/browse/QTBUG-2284

    QString path = qApp->applicationDirPath();

    QProcess process1;
    QProcess process2;
    process1.setProcessEnvironment(env);
    process2.setProcessEnvironment(env);
    process1.setWorkingDirectory(path);
    process2.setWorkingDirectory(path);


    process1.setStandardOutputProcess(&process2);

    process1.start("echo", {"\"pow 0\""});
    //process2.start("cec-client", {"-s","-d","2","/dev/cec1"});
    process2.start("cec-client", {"-s","\"-d 2\"","/dev/cec1"});
    process2.setProcessChannelMode(QProcess::ForwardedChannels);

    // Wait for it to start
    if(!process1.waitForStarted())
        return 0;

    bool retval = false;
    QByteArray buffer;
    while ((retval = process2.waitForFinished()));
    buffer.append(process2.readAll());

    ProcessHelper::Output o;

    if (!retval) {
        o.stdErr= process2.errorString();
        //return 1;
    }

    o.stdOut= buffer;

    QString a = o.ToString();
    zInfo("output:"+a);

    //stdout power status: on
    return false;
}
