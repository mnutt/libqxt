TEMPLATE = app
TARGET = QxtScheduleViewTest 
QT        += core gui
QXT       += core gui 
include($$QXT_SOURCE_TREE/src/qxtlibs.pri)

HEADERS   += qxtscheduleviewtest.h
SOURCES   += main.cpp \
    qxtscheduleviewtest.cpp
FORMS     += qxtscheduleviewtest.ui    
RESOURCES +=
