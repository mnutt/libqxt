TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += qxt no_keywords
QXT = berkeley core gui network sql web

# Input
SOURCES += main.cpp

# TODO: fix public QxtBDB headers NOT to include BDB headers!
win32:include(../../../depends.pri)
