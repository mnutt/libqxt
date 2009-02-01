TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
QXT += berkeley 
SOURCES += main.cpp
include(../../unit.pri)

# TODO: fix public QxtBDB headers NOT to include BDB headers!
win32:include(../../../../depends.pri)
