TEMPLATE     = lib
DESTDIR= .
TARGET 	     = QxtDesignerPlugins
DEPENDPATH  += .
INCLUDEPATH += ../src  ../src/gui ../deploy/include
CONFIG      += designer plugin debug_and_releas

HEADERS += QxtLabelPlugin.h  ../src/gui/QxtLabel.h
SOURCES += QxtLabelPlugin.cpp  ../src/gui/QxtLabel.cpp





CONFIG += build_all
 RESOURCES     = resources.qrc
