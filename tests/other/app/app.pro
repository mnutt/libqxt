TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += console
QXT += core gui
include($$QXT_SOURCE_TREE/src/qxtlibs.pri)

FORMS += mainwindow.ui tab.ui
HEADERS += mainwindow.h tab.h
SOURCES += main.cpp mainwindow.cpp tab.cpp
RESOURCES += app.qrc
