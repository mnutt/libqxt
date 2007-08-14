TARGET = QxtCrypto
DESTDIR = ../../deploy/libs/
DEPENDPATH += .
INCLUDEPATH     += . thirdparty ../core

DEFINES += BUILD_QXT_CRYPTO
win32: CONFIG += dll
QT = core
INCLUDEPATH += .
TEMPLATE = lib
MOC_DIR = .moc
OBJECTS_DIR = .obj
CONFIG += qxtbuild  convenience

SOURCES+= thirdparty/md5.cpp thirdparty/md4.cpp


HEADERS += qxthash.h 
SOURCES += qxthash.cpp

include(../../config.pri)

#doesn't actualy work. dunno what's wrong

#contains(DEFINES,HAVE_OPENSSL){
#HEADERS += qxtblowfish.h
#SOURCES += qxtblowfish.cpp
#LIBS+=-lssl
#}



