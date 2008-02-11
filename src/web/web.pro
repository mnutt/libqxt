TEMPLATE         = lib
CLEAN_TARGET     = QxtWeb
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../network
DEFINES         += BUILD_QXT_WEB
QT               = core network
QXT              = core network
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)
include(web.pri)
