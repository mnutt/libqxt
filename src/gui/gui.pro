TEMPLATE         = lib
CLEAN_TARGET     = QxtGui
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_GUI
QT               = core gui
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild
CONFIG          += link_prl
LIBS += -lX11 -lm -lXext
include(../../config.pri)
include(gui.pri)

win32:LIBS      += -luser32


