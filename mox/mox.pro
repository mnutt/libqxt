include (../config.pri)

DESTDIR= ../deploy/bin
VERSION = $$QXVERSION
TEMPLATE = app
TARGET = mox
DEPENDPATH += .
INCLUDEPATH += . ..
SOURCES += main.cpp
