TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += no_keywords
contains(DEFINES,HAVE_DB):contains(QXT_MODULES, berkeley):QXT += berkeley
contains(QXT_MODULES, core):QXT += core
contains(QXT_MODULES, gui):QXT += gui
contains(QXT_MODULES, network):QXT += network
contains(QXT_MODULES, sql):QXT += sql
contains(QXT_MODULES, web):QXT += web
contains(DEFINES,HAVE_ZEROCONF):contains(QXT_MODULES, zeroconf):QXT += zeroconf
include($$QXT_SOURCE_TREE/src/qxtlibs.pri)

# Input
SOURCES += main.cpp
