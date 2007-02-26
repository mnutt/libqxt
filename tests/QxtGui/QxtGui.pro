TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += test.h
FORMS += test.ui
SOURCES += main.cpp

CONFIG+=qxt
QXT+=gui
message($$QXT)
