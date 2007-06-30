TARGET          =  QxtDesignerPlugins
DESTDIR         = .lib
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../gui
win32: CONFIG   += dll
QT               = core gui
INCLUDEPATH     += .
VERSION          = 0.2.4
TEMPLATE         = lib
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONFIG      += designer plugin

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS+=target


HEADERS += QxtCheckComboBoxPlugin.h \
           QxtDesignerPlugin.h \
           QxtDesignerPlugins.h \
           QxtLabelPlugin.h \
           QxtPushButtonPlugin.h \
           QxtSpanSliderPlugin.h \
           QxtStringSpinBoxPlugin.h \
           QxtTreeWidgetPlugin.h
SOURCES += QxtCheckComboBoxPlugin.cpp \
           QxtDesignerPlugin.cpp \
           QxtDesignerPlugins.cpp \
           QxtLabelPlugin.cpp \
           QxtPushButtonPlugin.cpp \
           QxtSpanSliderPlugin.cpp \
           QxtStringSpinBoxPlugin.cpp \
           QxtTreeWidgetPlugin.cpp
RESOURCES += resources.qrc


CONFIG(debug, debug|release) {
        unix:  TARGET = $$join(TARGET,,,.debug)
        mac:   TARGET = $$join(TARGET,,,_debug)
        win32: TARGET = $$join(TARGET,,d)
}





