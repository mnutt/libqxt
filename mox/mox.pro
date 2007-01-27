include (../config.pri)

DESTDIR= ../deploy/bin
VERSION = $$QXVERSION
TEMPLATE = app
TARGET = mox
QT=core
DEPENDPATH += .
INCLUDEPATH += . ..
SOURCES += main.cpp
