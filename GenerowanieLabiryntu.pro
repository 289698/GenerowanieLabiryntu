#-------------------------------------------------
#
# Project created by QtCreator 2018-04-03T03:25:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GenerowanieLabiryntu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filemanaging.cpp \
    generating.cpp \
    drawing.cpp

HEADERS  += mainwindow.h \
    filemanaging.h \
    generating.h \
    drawing.h

FORMS    += mainwindow.ui
