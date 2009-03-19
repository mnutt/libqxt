TEMPLATE         = lib
CLEAN_TARGET     = QxtZeroconf
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../network
!macx:LIBS      += -ldns_sd
DEFINES         += BUILD_QXT_ZEROCONF
QT               = core network
QXT              = core network
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)
include(zeroconf.pri)
