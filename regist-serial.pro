#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T14:44:37
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = regist-serial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbconnect.cpp

HEADERS  += mainwindow.h \
    dbconnect.h \
    dbinfo.h

FORMS    += mainwindow.ui

RESOURCES += \
    window.qrc \
    meiryo.qrc

DISTFILES +=

