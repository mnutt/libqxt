CLEAN_TARGET     = QxtCrypto
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_CRYPTO
QT               = core
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)




HEADERS  += qxtcrypto.h
HEADERS  += qxthash.h

SOURCES  += qxthash.cpp
SOURCES  += thirdparty/md5.cpp
SOURCES  += thirdparty/md4.cpp

contains(DEFINES,HAVE_OPENSSL){
    HEADERS += qxtblowfish.h
    SOURCES += qxtblowfish.cpp
    LIBS    += -lssl
}
