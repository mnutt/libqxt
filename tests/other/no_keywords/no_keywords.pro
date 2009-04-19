TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += qxt no_keywords
!win32: QXT += berkeley
QXT += core crypto gui network sql web

# Input
SOURCES += main.cpp

# TODO: fix public QxtBDB headers NOT to include BDB headers!
win32:include(../../../depends.pri)
