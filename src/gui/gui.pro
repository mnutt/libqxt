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


#fix fucking debian
unix{
system(cat /etc/issue | grep Debian){
warning(detected Debian. will assume broken makespec.)
LIBS        +=  -lX11
}
}
