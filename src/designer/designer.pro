VERSION      = $$QXVERSION
TEMPLATE     = lib
TARGET       = QxtDesignerPlugins
DEPENDPATH  += .
INCLUDEPATH += . ../core ../gui ../kit ../../deploy/include 
unix :LIBS        += -L../../deploy/libs/ -lQxtKit  -lQxtCore  -lQxtGui
win32:LIBS        += -L../../deploy/libs/ -lQxtKit0 -lQxtCore0 -lQxtGui0
CONFIG      += designer plugin
TEMPLATE     = lib

RESOURCES    = resources.qrc

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS+=target


HEADERS += QxtDesignerPlugins.h \
           QxtDesignerPlugin.h \
           QxtCheckComboBoxPlugin.h \
           QxtLabelPlugin.h \
           QxtPushButtonPlugin.h \
           QxtSpanSliderPlugin.h \
           QxtStringSpinBoxPlugin.h \
           QxtTreeWidgetPlugin.h

SOURCES += QxtDesignerPlugins.cpp \
           QxtDesignerPlugin.cpp \
           QxtCheckComboBoxPlugin.cpp \
           QxtLabelPlugin.cpp \
           QxtPushButtonPlugin.cpp \
           QxtSpanSliderPlugin.cpp \
           QxtStringSpinBoxPlugin.cpp \
           QxtTreeWidgetPlugin.cpp


Parts=QxtDesignerPlugins QxtApplication QxtCheckComboBox QxtItemDelegate QxtPushButton QxtSpanSlider QxtStringSpinBox QxtTabWidget QxtTreeWidget QxtTreeWidgetItem


CONFIG(debug, debug|release) {
	unix:  TARGET = $$join(TARGET,,,.debug)
	mac:   TARGET = $$join(TARGET,,,_debug)
	win32: TARGET = $$join(TARGET,,d)
}
