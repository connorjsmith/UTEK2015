#-------------------------------------------------
#
# Project created by QtCreator 2015-01-24T12:38:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stocks-gui
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    StockView.cpp

HEADERS  += MainWindow.h quandl.h \
    StockView.h

FORMS    += MainWindow.ui
