TEMPLATE     = lib
DESTDIR=
TARGET 	     = QxtDesignerPlugins
DEPENDPATH  += .
INCLUDEPATH += ../src  ../src/gui ../deploy/include
CONFIG      += designer plugin debug_and_release

HEADERS += QxtLabelPlugin.h  ../src/gui/QxtLabel.h
SOURCES += QxtLabelPlugin.cpp  ../src/gui/QxtLabel.cpp



CONFIG(debug, debug|release) {
	unix: TARGET = $$join(TARGET,,,.debug)
	mac: TARGET = $$join(TARGET,,,_debug)
	win32: TARGET = $$join(TARGET,,d)
}

message($${TARGET})


CONFIG += build_all
RESOURCES     = resources.qrc
