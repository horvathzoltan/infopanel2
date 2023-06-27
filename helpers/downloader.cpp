#include <QCoreApplication>
#include <QProcess>

#include "downloader.h"
#include "processhelper.h"
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

QString Downloader::GetDownload_CurlCommand(const QString& downloadFolder,  const QList<DownloadFileName>& filelist)
{
    bool valid = !filelist.isEmpty();
    QString retVal;

    if(valid){
        static const QString CMD = QStringLiteral(R"(curl -L %1 --output-dir %2)");
        static const QString FN = QStringLiteral(R"(-o %2 %1)");
        static const QString INF = QStringLiteral(R"(Preparing to download[%3]: %1 as %2)");
        QString args;
        int counter=0;
        for(auto&a:filelist){
            if(!args.isEmpty()) args+=' ';
            QString fn = a.filename;
            args+=FN.arg(a.url).arg(fn);

            zInfo(INF.arg(a.url).arg(a.filename).arg(counter++));
        }
        retVal = CMD.arg(args).arg(downloadFolder);
    }
    zInfo("cmd:"+retVal);
    return retVal;
}


bool Downloader::Download_Curl(const QString& downloadFolder, const QList<DownloadFileName>& filelist)
{
    bool retVal = false;
    QString cmd = GetDownload_CurlCommand(downloadFolder, filelist);

    ProcessHelper::Output out = ProcessHelper::ShellExecute(cmd);
    bool ok = out.exitCode==0;
    if(ok){
        retVal = true;
    }
    return retVal;
}

/*
reparing to download[0]: http://pub.logcontrol.hu/images/neuron.jpg as 83edc33f-decc-4a20-b6cb-0929438e0d48
Preparing to download[1]: http://pub.logcontrol.hu/images/smidgeons.jpg as 638ec144-5738-43d0-b2a1-2ac70e5a490d
Preparing to download[2]: http://pub.logcontrol.hu/images/circles_1920x1200.jpg as 383a1951-fc3d-42d7-b7c4-368014a72522
Preparing to download[3]: http://pub.logcontrol.hu/images/cosmogony1920.jpg as 9e88616c-ae22-46a9-88d6-450d68f53d98
Preparing to download[4]: http://pub.logcontrol.hu/images/arctica1920.jpg as f99af722-9292-4b39-b66f-54e97d050f81
Preparing to download[5]: http://pub.logcontrol.hu/images/202-1920.jpg as 4e2efd31-89b8-4dbc-b2c4-5fd39b02dc66
Preparing to download[6]: http://pub.logcontrol.hu/images/skysong2.jpg as 1344803a-9f15-447d-8491-694d7209ead1
Preparing to download[7]: http://pub.logcontrol.hu/images/valley2k.jpg as cd4e29c9-bb9d-418c-ae13-7f1f4534bb4f
Preparing to download[8]: http://pub.logcontrol.hu/images/thetismoon.jpg as 6cd09f5a-5384-4a34-93d5-89e3efb5e664
Preparing to download[9]: http://pub.logcontrol.hu/images/newborn.jpg as 733f69f5-e420-491a-b396-8bf479ebdefd
Preparing to download[10]: http://pub.logcontrol.hu/images/pyre.jpg as 302e8022-de19-483e-b904-8df6eae0a0aa
Preparing to download[11]: http://pub.logcontrol.hu/images/202-1920.jpg as cff74e18-51ea-43fe-8a92-9e739736d0c7
Preparing to download[12]: http://pub.logcontrol.hu/images/crucibleplanet1920.jpg as 8bc3da97-1ee2-472d-87e4-a64c088b469c
Preparing to download[13]: http://pub.logcontrol.hu/images/223-1920.jpg as 77454658-e648-41f9-8e0f-bdcb847eda5f
Preparing to download[14]: http://pub.logcontrol.hu/images/spellcraft.jpg as a79f6414-8bab-47af-ab94-d0440b2293cd
Preparing to download[15]: http://pub.logcontrol.hu/images/cancer.jpg as 3b887c2f-d444-44f2-b04d-ec5ca33f1c5a
Preparing to download[16]: http://pub.logcontrol.hu/images/sunsetfog.jpg as e81e3ea0-bd89-41f3-ba05-ee9e9038c62a
*/
