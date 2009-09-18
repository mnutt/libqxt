SOURCES += main.cpp \
threadtestcontroller.cpp \
locktestclient.cpp \
HelperClass.cpp
TEMPLATE = app
TARGET = ../bin/qxtfilelock

QT -= gui
QT += core \
network
CONFIG += console
QXT += core
include($$QXT_SOURCE_TREE/src/qxtlibs.pri)

HEADERS += threadtestcontroller.h \
locktestclient.h \
HelperClass.h
