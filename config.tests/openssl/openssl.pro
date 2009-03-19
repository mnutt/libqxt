win32:include(../../depends.pri)
CONFIG -= app_bundle
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += main.cpp
!win32:LIBS+= -lcrypto -lssl
QT=core
CONFIG -= app_bundle
