TEMPLATE         = lib
CLEAN_TARGET     = QxtBerkeley
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_BERKELEY
QT               = core
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)
include(berkeley.pri)

!win32:LIBS     += -ldb