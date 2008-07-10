TEMPLATE         = lib
CLEAN_TARGET     = QxtCore
DEPENDPATH      += .
INCLUDEPATH     += .
DEFINES         += BUILD_QXT_CORE
QT               = core
QXT              =
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)
include(core.pri)
include(logengines/logengines.pri)
