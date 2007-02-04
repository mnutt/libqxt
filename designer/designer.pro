TEMPLATE     = lib
DESTDIR=
TARGET       = QxtDesignerPlugins
DEPENDPATH  += .
INCLUDEPATH += ../src  ../src/gui ../src/core ../deploy/include
CONFIG      += designer plugin debug_and_release build_all
RESOURCES    = resources.qrc
LIBS+= -L../deploy/libs/ -lQxtGui


HEADERS += QxtDesignerPlugins.h \
           QxtDesignerPlugin.h \
           QxtLabelPlugin.h       \
           QxtPushButtonPlugin.h  \
           QxtTreeWidgetPlugin.h  

SOURCES += QxtDesignerPlugins.cpp \
           QxtDesignerPlugin.cpp \
           QxtLabelPlugin.cpp  \ 
          QxtPushButtonPlugin.cpp \
           QxtTreeWidgetPlugin.cpp 

CONFIG(debug, debug|release) {
	unix: TARGET = $$join(TARGET,,,.debug)
	mac: TARGET = $$join(TARGET,,,_debug)
	win32: TARGET = $$join(TARGET,,d)
}
