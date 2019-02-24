#-------------------------------------------------
#
# Project created by QtCreator 2017-09-08T21:24:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    codeeditor.cpp \
    myhighlighter.cpp

HEADERS  += widget.h \
    commonhelper.h \
    codeeditor.h \
    typedef.h \
    myhighlighter.h

FORMS    += \
    widget.ui

RESOURCES += \
    example.qrc
CONFIG+= console
