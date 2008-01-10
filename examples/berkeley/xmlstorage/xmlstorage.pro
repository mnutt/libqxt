TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

CONFIG+=qxt
QXT+=berkeley


HEADERS += node.h mainwindow.h xml2bdb.h model.h
FORMS += mainwindow.ui
SOURCES += node.cpp main.cpp mainwindow.cpp xml2bdb.cpp model.cpp

