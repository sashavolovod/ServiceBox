QT       += core gui sql widgets

TARGET = servicebox
TEMPLATE += app

SOURCES += main.cpp\
    db.cpp \
    mainwindow.cpp \
    runguard.cpp

RESOURCES += \
    systray.qrc

HEADERS += \
    mainwindow.h \
    runguard.h
