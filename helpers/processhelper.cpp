#include "processhelper.h"
#include "helpers/logger.h"

#include <QCoreApplication>
#include <QElapsedTimer>
#include <QProcess>
#include <iostream>

const QString ProcessHelper::SEPARATOR = '\n'+QStringLiteral("stderr")+'\n';
bool ProcessHelper::_verbose = false;

QString ProcessHelper::Output::ToString(){
    QString e;

    if(!stdOut.isEmpty())
    {
        if(!e.isEmpty()) e+=SEPARATOR;
        e+=stdOut;
    }
    if(!stdErr.isEmpty())
    {
        if(!e.isEmpty()) e+=SEPARATOR;
        e+=stdErr;
    }
    if(!e.isEmpty()) e+=SEPARATOR;
    e+=QStringLiteral("exitCode: %1").arg(exitCode);
    return e;
}

//auto e = Execute3("/bin/bash", {"-c", cmd});//'\"'
//ProcessHelper::Output ProcessHelper::Execute(const QString& str){
//    Model m = Model::Parse(str);
//    ProcessHelper::Output e = Execute3(m);

//    return e;
//}

//auto e = Execute3("/bin/bash", {"-c", "echo \"Aladar123\" | sudo -S -k "+ str});
//ProcessHelper::Output ProcessHelper::ExecuteSudo(const QString& str){
//    Model m2 = Model::Parse(str);
//    m2.Sudo();
//    Model m1 = m2.InsertPasswd("Aladar123");

//    ProcessHelper::Output e = Execute3({m1, m2});

//    return e;
//}

ProcessHelper::Output ProcessHelper::ExecutePiped(const QList<Model>& models){
    QList<QProcess*> processes;

    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LD_LIBRARY_PATH", "/usr/lib"); // workaround - https://bugreports.qt.io/browse/QTBUG-2284
    static auto path = QCoreApplication::applicationDirPath();

    for(int i=0;i<models.length();i++){
        QProcess* process = new QProcess();
        process->setProcessEnvironment(env);
        process->setWorkingDirectory(path);
        //process->setProcessChannelMode(QProcess::MergedChannels);
        processes.append(process);
    }
//    int prev_ix = -1;
//    for(int i=0;i<models.length();i++)
//    {
//        if(prev_ix>-1)
//            processes[prev_ix]->setProcessChannelMode(QProcess::ForwardedChannels);
//            //processes[prev_ix]->setStandardOutputProcess(processes[i]);
//        prev_ix = i;
//    }
    if(processes.length()<2) return {};
    QProcess *process1 = processes[0];
    QProcess *process2 = processes[1];

    process1->setStandardOutputProcess(process2);

    process1->start(models[0].cmd,models[0].args);
    process2->start(models[1].cmd,models[1].args);
    process2->setProcessChannelMode(QProcess::ForwardedChannels);

    // Wait for it to start
    if(!process1->waitForStarted())
        return {};

    bool retval = false;
    QByteArray buffer;
    while ((retval = process2->waitForFinished()));
    buffer.append(process2->readAll());

    Output o;

    if (!retval) {
        o.stdErr= process2->errorString();
        //return 1;
    }

    o.stdOut= buffer;



    QList<Output> outputs;
    outputs.append(o);
    auto e = outputs.last();

    return e;
}

ProcessHelper::Output ProcessHelper::ShellExecute(const QString &cmd, int timeout_millis)
{
    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QProcess process;

    // process beállítása
    // workaround - https://bugreports.qt.io/browse/QTBUG-2284
    env.insert("LD_LIBRARY_PATH", "/usr/lib");
    process.setProcessEnvironment(env);
    QString path = qApp->applicationDirPath();
    process.setWorkingDirectory(path);

    // process indítása
    QElapsedTimer t;
    t.start();
    process.start("/bin/sh", {"-c", cmd});
    if(!process.waitForStarted()) return{};
    process.waitForFinished(timeout_millis);

    ProcessHelper::Output o;
    o.elapsedMillis = t.elapsed();
    o.stdOut  = process.readAllStandardOutput();
    o.stdErr = process.readAllStandardError();
    o.exitCode = process.exitCode();

    return o;
}

ProcessHelper::Output ProcessHelper::Execute3(const QList<Model>& models){

    QList<QProcess*> processes;

    QString t;
    for(auto&m:models){
        if(!t.isEmpty())t+=" | ";
        t+=m.toString();
    }
    if(_verbose) zInfo("cmd:"+t);

    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LD_LIBRARY_PATH", "/usr/lib"); // workaround - https://bugreports.qt.io/browse/QTBUG-2284
    static auto path = QCoreApplication::applicationDirPath();

    for(int i=0;i<models.length();i++){
        QProcess* process = new QProcess();
        process->setProcessEnvironment(env);
        process->setWorkingDirectory(path);
        //process->setProcessChannelMode(QProcess::MergedChannels);
        processes.append(process);
    }

    int prev_ix = -1;
    for(int i=0;i<models.length();i++)
    {
        if(prev_ix>-1)
            processes[prev_ix]->setStandardOutputProcess(processes[i]);
        prev_ix = i;
    }

    //QTextStream cout2(stderr);

    QList<Output> outputs;
    QByteArray o2;

    for(int i=0;i<models.length();i++)
    {
        auto&m = models[i];
        QProcess *p = processes[i];

        //QDebug dbg = qDebug();//.nospace().noquote();
        //QTextStream stream(p);

        auto readyR = [p, &o2, &m]()
        {
            p->setReadChannel(QProcess::StandardError);
            while (!p->atEnd()) {
                QString d = p->readAll();
                if(m.showStdErr) std::cerr << d.toStdString();
                //auto o3 = d.toStdString();
                o2.append(d.toUtf8());
            }
        };

        QObject::connect(p, &QProcess::readyReadStandardError,readyR);


//        if(m.args.isEmpty())
//            p->start(m.cmd);
//        else
        p->start(m.cmd,m.args);
    }


    for(int i=0;i<models.length();i++)
    {
        auto&m = models[i];
        QProcess *p = processes[i];

        if (!p->waitForStarted(-1))
        {
            if(_verbose) zInfo("Could not start");
            return {"","",1};
        }


        bool isFinished = p->waitForFinished(m.timeout);

        //QObject::disconnect(p, &QIODevice::readyRead, nullptr, nullptr);

        if(!isFinished)
        {
            p->close();
            //return {"","",1};
        }
        //QString(o2)+
        Output output{ .stdOut = p->readAllStandardOutput(),
                      .stdErr = QString(o2)+p->readAllStandardError(),
                      .exitCode = p->exitCode()};

        outputs.append(output);
    }

    //QProcess* process2 = processes.last();

    //    Output e{process2->readAllStandardOutput(),
    //                process2->readAllStandardError(),
    //                process2->exitCode()};

    for(auto p:qAsConst(processes)){
        delete p;
    }

    auto e = outputs.last();

    return e;
}

// QCoreApplication::applicationDirPath();
//ProcessHelper::Output ProcessHelper::Execute3(const QString& cmd, const QStringList& args, int timeout){
ProcessHelper::Output ProcessHelper::Execute3(const Model& m){
    if(m.cmd.isEmpty()) return {};

    QCoreApplication::applicationDirPath();
    QProcess process;
    //process.setProcessChannelMode(QProcess::ForwardedChannels);
    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LD_LIBRARY_PATH", "/usr/lib"); // workaround - https://bugreports.qt.io/browse/QTBUG-2284
    process.setProcessEnvironment(env);

    QString path = m.path.isEmpty()?QCoreApplication::applicationDirPath():m.path;

    process.setWorkingDirectory(path);

//    if(m.args.isEmpty())
//        process.start(m.cmd);
//    else
    process.start(m.cmd,m.args);

    if (!process.waitForStarted(-1))
    {
        if(_verbose) zInfo("Could not start");
        return {"","",1};
    }

    bool isFinished = process.waitForFinished(m.timeout);

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

ProcessHelper::Model ProcessHelper::Model::Parse(const QString &str)
{
    if(str.isEmpty()) return {};
    QStringList tokens = str.split(' ', Qt::SkipEmptyParts);

    if(tokens.length()<1) return {};
    if(tokens.length()==1) return {.cmd = tokens[0], .args = {}, .timeout=-1};
    return {.cmd = tokens[0], .args = tokens.mid(1), .timeout=-1};
}

QList<ProcessHelper::Model> ProcessHelper::Model::ParseAsSudo(const QString &str, const QString& pwd)
{
    QList<ProcessHelper::Model> m;
    if(str.isEmpty()) return m;
    Model m1 = Model::Parse(str);
    m1.Sudo();
    if(!pwd.isEmpty())
    {
        Model m0 = m1.InsertPasswd(pwd);
        m.append(m0);
    }
    m.append(m1);
    return m;
}


void ProcessHelper::Model::Sudo()
{
    args.insert(0, cmd);
    cmd = "sudo";
}

ProcessHelper::Model ProcessHelper::Model::InsertPasswd(const QString &p)
{
    Model m1 = {.cmd = "echo", .args = {p}, .timeout=-1};
    if(cmd.toLower()=="sudo")
        args.insert(0, "-S");
    return m1;
}

QString ProcessHelper::Model::toString() const
{
    if(args.isEmpty()) return cmd;
    return cmd+" "+ args.join(' ');
}


//ProcessHelper::Output ProcessHelper::Execute2(const QString& cmd){
//    //qint64 pid;
//    QProcess process;
//    process.setProcessChannelMode(QProcess::ForwardedChannels);
//    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
//    env.insert("LD_LIBRARY_PATH", "/usr/lib"); // workaround - https://bugreports.qt.io/browse/QTBUG-2284
//    process.setProcessEnvironment(env);
//    static auto path = QCoreApplication::applicationDirPath();
//    process.setWorkingDirectory(path);

//    process.start(cmd);
//    process.waitForFinished(-1); // will wait forever until finished
//    return {process.readAllStandardOutput(), process.readAllStandardError(), process.exitCode()};
//}
