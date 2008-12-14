TEMPLATE         = lib
CLEAN_TARGET     = QxtViral
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_VIRAL
QT               = core
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild
CONFIG          += link_prl
include(../../config.pri)
include(viral.pri)

LIBS            +=  -lviral_dom

