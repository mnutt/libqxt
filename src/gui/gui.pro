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
include(../../config.pri)
include(gui.pri)

win32:LIBS      += -luser32
# Debian and derivatives pass --no-undefined to the linker, which
# means that each library must explicitly link to all dependencies 
# than assuming that the application or another library will bring
# in the necessary symbols at run time.
x11:contains(QMAKE_LFLAGS, "-Wl,--no-undefined"):LIBS += -lX11 -lXext -lm

