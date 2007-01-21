include (../config.pri)

DESTDIR= .
VERSION = $$QXVERSION
TEMPLATE = app
TARGET = mox
DEPENDPATH += .
INCLUDEPATH += . ..
SOURCES += main.cpp
