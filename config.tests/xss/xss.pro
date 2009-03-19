win32:include(../../depends.pri)
CONFIG -= app_bundle
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += main.cpp
!win32:LIBS+=-lXss
