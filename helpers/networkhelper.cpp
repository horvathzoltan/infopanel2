#include "networkhelper.h"

#include <QNetworkInterface>

QString NetworkHelper::hwid_ethernet(){
    auto a= QNetworkInterface::allInterfaces();
    for(auto&i:a)
    {
        if(i.type()==QNetworkInterface::Ethernet) return i.hardwareAddress();
    }
    return QString();
}
