#-------------------------------------------------
#
# Project created by QtCreator 2016-06-20T13:50:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cpp-test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    image.cpp \
    mylabel.cpp \
    brush.cpp \
    line.cpp \
    history.cpp

HEADERS  += mainwindow.h \
    image.h \
    mylabel.h \
    brush.h \
    line.h \
    history.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
