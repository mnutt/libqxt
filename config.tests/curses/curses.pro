win32:include(../../depends.pri)
CONFIG -= app_bundle
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += main.cpp
LIBS += -lpanel -lncurses
CONFIG -= qt
CONFIG -= app_bundle
