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
    bi/cechelper.cpp \
    bi/mastermode.cpp \
    bi/mode.cpp \
    bi/processrequest.cpp \
    bi/slavemode.cpp \
    bi/tcpsocketclient.cpp \
    bi/tcpsocketserver.cpp \
    bi/webapihelper.cpp \
    global.cpp \
    helpers/commandlineparserhelper.cpp \
    helpers/downloader.cpp \
    helpers/filenamehelper.cpp \
    helpers/inihelper.cpp \
    helpers/libcechelper.cpp \
    helpers/logger.cpp \
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
    webapi/device.cpp \
    webapi/devicerequest.cpp \
    webapi/deviceresponse.cpp

HEADERS += \
    bi/cechelper.h \
    bi/mastermode.h \
    bi/mode.h \
    bi/processrequest.h \
    bi/slavemode.h \
    bi/tcpsocketclient.h \
    bi/tcpsocketserver.h \
    bi/webapihelper.h \
    global.h \
    helpers/commandlineparserhelper.h \
    helpers/downloader.h \
    helpers/filenamehelper.h \
    helpers/inihelper.h \
    helpers/libcechelper.h \
    helpers/logger.h \
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
    webapi/device.h \
    webapi/devicerequest.h \
    webapi/deviceresponse.h \
    webapi/deviceresponsecodes.h

FORMS += \
    form3.ui \
    frame2.ui \
    mainwindow.ui

contains(QMAKESPEC,.*linux-rasp-pi\d*-.*){
    message(rpi)
    CONFIG += rpi
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


