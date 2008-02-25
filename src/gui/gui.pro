TEMPLATE         = lib
CLEAN_TARGET     = QxtGui
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_GUI
QT               = core gui
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)
include(gui.pri)

win32:LIBS      += -luser32
x11:LIBS        += -lX11
