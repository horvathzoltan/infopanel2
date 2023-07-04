QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = infopanel2
DEFINES += TARGI=$$TARGET
message( "TARGET = "$$TARGET )

# ezzel kikapcsolja a cect
#DEFINES += LIBCEC

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bi/alivemanager.cpp \
    bi/cechelper.cpp \
    bi/cecmanager.cpp \
    bi/constants.cpp \
    bi/downloadfilemetadata.cpp \
    bi/downloadmanager.cpp \
    bi/logmanager.cpp \
    bi/mode.cpp \
    bi/processrequest.cpp \
    bi/pubimages.cpp \
    bi/slideshowitem.cpp \
    bi/slideshowmanager.cpp \
    bi/tcpsocketclient.cpp \
    bi/tcpsocketserver.cpp \
    bi/testmode.cpp \
    bi/webapimanager.cpp \
    global.cpp \
    helpers/commandlineparserhelper.cpp \
    helpers/downloader.cpp \
    bi/filenamehelper.cpp \
    helpers/httpresponse.cpp \
    helpers/inihelper.cpp \
    helpers/jsonvaluehelper.cpp \
    helpers/libcechelper.cpp \
    helpers/logger.cpp \
    helpers/nameof.cpp \
    helpers/networkhelper.cpp \
    helpers/processhelper.cpp \
    helpers/screenhelper.cpp \
    helpers/shortguid.cpp \
    helpers/signalhelper.cpp \
    helpers/textfilehelper.cpp \
    form3.cpp \
    frame2.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    webapi/application.cpp \
    webapi/applicationproblem.cpp \
    webapi/applicationtheme.cpp \
    webapi/device.cpp \
    webapi/loguploadmodel.cpp \
    webapi/requestmodels/devicealiverequestmodel.cpp \
    webapi/requestmodels/devicerequestmodel.cpp \
    webapi/requestmodels/pubapplicationdatarequestmodel.cpp \
    webapi/pubapplicationdata.cpp \
    webapi/requestmodels/publogrequestmodel.cpp \
    webapi/responsemodels/devicealiveresponsemodel.cpp \
    webapi/responsemodels/deviceresponsemodel.cpp \
    webapi/pubimageitem.cpp \
    webapi/responsemodels/pubapplicationdataresponsemodel.cpp

HEADERS += \
    bi/alivemanager.h \
    bi/cechelper.h \
    bi/cecmanager.h \
    bi/constants.h \
    bi/downloadfilemetadata.h \
    bi/downloadmanager.h \
    bi/logmanager.h \
    bi/mode.h \
    bi/processrequest.h \
    bi/pubimages.h \
    bi/slideshowitem.h \
    bi/slideshowmanager.h \
    bi/tcpsocketclient.h \
    bi/tcpsocketserver.h \
    bi/testmode.h \
    bi/webapimanager.h \
    global.h \
    helpers/commandlineparserhelper.h \
    helpers/downloader.h \
    bi/filenamehelper.h \
    helpers/httpresponse.h \
    helpers/inihelper.h \
    helpers/jsonvaluehelper.h \
    helpers/libcechelper.h \
    helpers/logger.h \
    helpers/nameof.h \
    helpers/networkhelper.h \
    helpers/processhelper.h \
    helpers/screenhelper.h \
    helpers/shortguid.h \
    helpers/signalhelper.h \
    helpers/stringify.h \
    helpers/textfilehelper.h \
    form3.h \
    frame2.h \
    mainwindow.h \
    settings.h \
    webapi/application.h \
    webapi/applicationproblem.h \
    webapi/applicationtheme.h \
    webapi/device.h \
    webapi/loguploadmodel.h \
    webapi/requestmodels/devicealiverequestmodel.h \
    webapi/requestmodels/devicerequestmodel.h \
    webapi/requestmodels/pubapplicationdatarequestmodel.h \
    webapi/loginmodes.h \
    webapi/pubapplicationdata.h \
    webapi/requestmodels/publogrequestmodel.h \
    webapi/responsemodels/devicealiveresponsemodel.h \
    webapi/responsemodels/deviceresponsemodel.h \
    webapi/pubimageitem.h \
    webapi/responsemodels/pubapplicationdataresponsemodel.h

FORMS += \
    form3.ui \
    frame2.ui \
    mainwindow.ui

contains(QMAKESPEC,.*linux-rasp-pi\d*-.*){
    message(rpi)
    CONFIG += rpi
    DEFINES += RASPBERRY_PI
}

unix:rpi:{
message(LIBS added for raspberry_pi)
#LIBS += -lwiringPi
#LIBS += -lnfc -lpthread
#LIBS += -lusb-1.0
defined(LIBCEC) {
    message(LIBCEC defined)
    LIBS += -lcec
    LIBS += -ldl
} else {
    message(no LIBCEC)
}
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    settings.txt


