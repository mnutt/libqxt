TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
QXT += berkeley 
SOURCES += main.cpp
QMAKE_CLEAN += test.db
include(../../unit.pri)

# TODO: fix public QxtBDB headers NOT to include BDB headers!
win32:include(../../../../depends.pri)
