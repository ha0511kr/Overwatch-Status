#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T18:35:03
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Overwatch_Stats
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui



unix|win32: LIBS += -lcurl
