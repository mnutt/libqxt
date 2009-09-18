TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += no_keywords
QXT = berkeley core gui network sql web
include($$QXT_SOURCE_TREE/src/qxtlibs.pri)

# Input
SOURCES += main.cpp

# TODO: fix public QxtBDB headers NOT to include BDB headers!
win32:include(../../../depends.pri)
