TEMPLATE         = lib
CLEAN_TARGET     = QxtDesignerPlugins
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../gui
DEFINES         +=
QT               = core gui
QXT              = core gui
CONVENIENCE     +=
CONFIG          += designer plugin qxtbuild

include(../../config.pri)
include(designer.pri)

target.path      = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS        += target
RESOURCES       += resources.qrc
