TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mazeclass.cpp \
    mazegen.cpp \
    mazeprint.cpp \
    launchgame.cpp

HEADERS += \
    mazeclass.h \
    mazegen.h \
    mazeprint.h \
    launchgame.h
