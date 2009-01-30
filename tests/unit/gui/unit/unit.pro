TEMPLATE     = app
TARGET       = gui
DEPENDPATH  += .
INCLUDEPATH += .
CONFIG      += qtestlib qxt
QXT         += core gui
SOURCES     += main.cpp
include(../../test.pri)
