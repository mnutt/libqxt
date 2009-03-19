win32:include(../../depends.pri)
unix:!macx:LIBS += -lavahi-common -lavahi-client
CONFIG -= app_bundle
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += zeroconf.cpp
QT=core
CONFIG -= app_bundle
