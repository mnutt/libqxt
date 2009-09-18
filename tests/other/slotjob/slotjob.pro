TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
QXT+=core
include($$QXT_SOURCE_TREE/src/qxtlibs.pri)
SOURCES += main.cpp
include(../../test.pri)
