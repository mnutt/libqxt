include(../../features/qxtfunctions.prf)
TEMPLATE         = lib
CLEAN_TARGET     = QxtCrypto
TARGET           = $$qxtLibraryTarget($$CLEAN_TARGET)
DESTDIR          = ../../deploy/libs/
DEPENDPATH      += .
INCLUDEPATH     += . thirdparty ../core
DEFINES         += BUILD_QXT_CRYPTO
win32: CONFIG   += dll
QT               = core
QXT              =
INCLUDEPATH     += .
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
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
