TEMPLATE         = lib
CLEAN_TARGET     = QxtCrypto
DEPENDPATH      += .
INCLUDEPATH     += . thirdparty ../core
DEFINES         += BUILD_QXT_CRYPTO
QT               = core
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)
include(crypto.pri)
