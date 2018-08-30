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
    service.cpp \
    messageedit.cpp \
    addservicedialog.cpp \
    comboboxitem.cpp \
    servicedetail.cpp \
    servicedetailtablemodel.cpp

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
    dbhelper.h \
    service.h \
    messageedit.h \
    addservicedialog.h \
    comboboxitem.h \
    servicedetail.h \
    servicedetailtablemodel.h

FORMS += \
    logindialog.ui \
    addservicedialog.ui

CONFIG += c++11

win32:RC_ICONS += if_package_settings_1441.ico

