TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mazeclass.cpp \
    mazegen.cpp \
    tempprint.cpp \
    tempwalking.cpp

HEADERS += \
    mazeclass.h \
    mazegen.h \
    tempprint.h \
    tempwalking.h
