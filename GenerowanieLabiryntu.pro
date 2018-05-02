#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T19:42:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GenerowanieLabiryntu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generating.cpp \
    mazemanagment.cpp \
    filedialog.cpp \
    filemanagment.cpp

HEADERS  += mainwindow.h \
    generating.h \
    mazemanagment.h \
    filedialog.h \
    filemanagment.h \
    mazestruct.h

FORMS    += mainwindow.ui \
    filedialog.ui
