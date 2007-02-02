TEMPLATE     = lib
DESTDIR=
TARGET       = QxtDesignerPlugins
DEPENDPATH  += .
INCLUDEPATH += ../src  ../src/gui ../deploy/include
CONFIG      += designer plugin debug_and_release build_all
RESOURCES    = resources.qrc

HEADERS += QxtDesignerPlugins.h \
           QxtDesignerPlugin.h \
           QxtLabelPlugin.h        ../src/gui/QxtLabel.h \
           QxtPushButtonPlugin.h   ../src/gui/QxtPushButton.h \
           QxtTreeWidgetPlugin.h   ../src/gui/QxtTreeWidget.h \
                                   ../src/gui/QxtTreeWidget_p.h \
                                   ../src/gui/QxtItemDelegate.h
SOURCES += QxtDesignerPlugins.cpp \
           QxtDesignerPlugin.cpp \
           QxtLabelPlugin.cpp      ../src/gui/QxtLabel.cpp \
           QxtPushButtonPlugin.cpp ../src/gui/QxtPushButton.cpp \
           QxtTreeWidgetPlugin.cpp ../src/gui/QxtTreeWidget.cpp \
                                   ../src/gui/QxtItemDelegate.cpp

CONFIG(debug, debug|release) {
	unix: TARGET = $$join(TARGET,,,.debug)
	mac: TARGET = $$join(TARGET,,,_debug)
	win32: TARGET = $$join(TARGET,,d)
}
