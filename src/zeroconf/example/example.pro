TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += . ..
CONFIG += qxt
QXT = core network
LIBS += -framework QxtZeroconf

# Input
HEADERS += foo.h
SOURCES += test.cpp
