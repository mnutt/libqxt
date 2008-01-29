CLEAN_TARGET     = QxtCrypto
DEPENDPATH      += .
INCLUDEPATH     += . thirdparty ../core
DEFINES         += BUILD_QXT_CRYPTO
QT               = core
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild
TEMPLATE         = lib
include(../../config.pri)




HEADERS  += qxtcrypto.h
HEADERS  += qxthash.h

SOURCES  += qxthash.cpp
SOURCES  += thirdparty/md5.cpp
SOURCES  += thirdparty/md4.cpp

contains(DEFINES,HAVE_OPENSSL){
    HEADERS += qxtblowfish.h
    SOURCES += qxtblowfish.cpp
    !win32:LIBS    += -lcrypto
}
