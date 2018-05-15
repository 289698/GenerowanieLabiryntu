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
    maze.cpp \
    filemanagment.cpp \
    windialog.cpp \
    settingsdialog.cpp \
    leaderdialog.cpp

HEADERS  += mainwindow.h \
    generating.h \
    mazemanagment.h \
    filedialog.h \
    maze.h \
    filemanagment.h \
    windialog.h \
    settingsdialog.h \
    leaderdialog.h

FORMS    += mainwindow.ui \
    filedialog.ui \
    windialog.ui \
    settingsdialog.ui \
    leaderdialog.ui
