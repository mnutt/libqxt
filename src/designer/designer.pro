VERSION      = $$QXVERSION
TEMPLATE     = lib
TARGET       = QxtDesignerPlugins
DEPENDPATH  += .
INCLUDEPATH += . ../core ../gui ../kit ../../deploy/include 
LIBS        += -L../../deploy/libs/ -lQxtKit -lQxtCore -lQxtGui
CONFIG      += designer plugin debug_and_release build_all
TEMPLATE     = lib

RESOURCES    = resources.qrc



HEADERS += QxtDesignerPlugins.h \
           QxtDesignerPlugin.h \
           QxtLabelPlugin.h       \
           QxtPushButtonPlugin.h  \
           QxtTreeWidgetPlugin.h \
           QxtCheckComboBoxPlugin.h

SOURCES += QxtDesignerPlugins.cpp \
           QxtDesignerPlugin.cpp \
           QxtLabelPlugin.cpp  \ 
           QxtPushButtonPlugin.cpp \
           QxtTreeWidgetPlugin.cpp \
           QxtCheckComboBoxPlugin.cpp


Parts=QxtDesignerPlugins QxtPushButton QxtItemDelegate QxtTreeWidget QxtTreeWidgetItem QxtTabWidget QxtApplication QxtCheckComboBox



CONFIG(debug, debug|release) {
	unix:  TARGET = $$join(TARGET,,,.debug)
	mac:   TARGET = $$join(TARGET,,,_debug)
	win32: TARGET = $$join(TARGET,,d)
}
