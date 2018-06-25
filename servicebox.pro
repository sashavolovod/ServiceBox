QT       += core gui sql widgets

TARGET = servicebox
TEMPLATE += app

SOURCES += main.cpp\
    mainwindow.cpp \
    runguard.cpp \
    servicetablemodel.cpp \
    equipmentservice.cpp \
    aes.cpp \
    logindialog.cpp \
    aesqt.cpp \
    dbhelper.cpp \
    service.cpp

RESOURCES += \
    systray.qrc

HEADERS += \
    mainwindow.h \
    runguard.h \
    servicetablemodel.h \
    equipmentservice.h \
    aes.h \
    aesqt.h \
    logindialog.h \
    common.h \
    dbhelper.h \
    service.h

FORMS += \
    logindialog.ui
