TARGET          =  QxtNetwork
#DESTDIR         = .lib
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_NETWORK
win32: CONFIG   += dll
QT               = core network
INCLUDEPATH     += .
TEMPLATE         = lib
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONFIG += qxtbuild  convenience



HEADERS +=  qxtrpcpeer.h
SOURCES += qxtrpcpeer.cpp

include(../../config.pri)
contains(DEFINES,HAVE_OPENSSL){
HEADERS += qxtblowfish.h 
SOURCES += qxtblowfish.cpp
LIBS+=-lssl
}


#HEADERS += qxtnamedpipe.h
#unix: SOURCES += qxtnamedpipe_unix.cpp 
