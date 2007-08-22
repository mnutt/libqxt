SOURCES += main.cpp \
threadtestcontroller.cpp \
locktestclient.cpp \
HelperClass.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
	  debug
TARGET = ../bin/qxttestsuite

QT -= gui
QT += core \
network
CONFIG += qxt
QXT += core
HEADERS += threadtestcontroller.h \
locktestclient.h \
HelperClass.h
