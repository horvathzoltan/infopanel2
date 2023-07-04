#include "filenamehelper.h"
#include "settings.h"

#include <QCoreApplication>
#include <QDir>

extern Settings settings;


bool FileNameHelper::_inited= false;
QString FileNameHelper::_appDir;

bool FileNameHelper::Init(const QString &appDir)
{
    _inited = false;
    _appDir = appDir;
    _inited = true;
    return true;
}

QString FileNameHelper::SettingsFileName()
{
    if(!_inited) return {};
    return QDir(_appDir).filePath("settings.ini");
}

QString FileNameHelper::GetSlideShowFileName(){
    if(!_inited) return {};
    return QDir(settings.DownloadDirectory()).filePath("SlideshowManager.ini");
}

QString FileNameHelper::GetCounterFileName(const QString& fn){
    if(!_inited) return {};
    return QDir(settings.CounterDirectory()).filePath(fn);
}

QString FileNameHelper::GetLogFileName(const QString& fn){
    if(!_inited) return {};
    return QDir(settings.LogDirectory()).filePath(fn);
}

QString FileNameHelper::GetDownloadFolder(){
    if(!_inited) return {};
    return settings.DownloadDirectory();
}

QStringList FileNameHelper::GetDownloadFolderContent(){
    if(!_inited) return {};
    QDir downloadDir(settings.DownloadDirectory());
    auto fileNameList = downloadDir.entryList(QDir::Files);
    return fileNameList;
}

QString FileNameHelper::GetDownloadFileName(const QString& fn){
    if(!_inited) return {};
    return QDir(settings.DownloadDirectory()).filePath(fn);
}

qint64 FileNameHelper::GetFileSize(const QString& fn){
    if(!_inited) return {};
    return QFile(fn).size();
}
