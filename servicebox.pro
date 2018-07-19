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
    comboboxitem.cpp

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
    service.h \
    messageedit.h \
    addservicedialog.h \
    comboboxitem.h

FORMS += \
    logindialog.ui \
    addservicedialog.ui
