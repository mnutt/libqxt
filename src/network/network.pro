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



HEADERS +=  QxtRPCPeer.h
SOURCES += QxtRPCPeer.cpp

include(../../config.pri)
contains(DEFINES,HAVE_OPENSSL){
HEADERS += QxtBlowFish.h 
SOURCES += QxtBlowFish.cpp
LIBS+=-lssl
}


#HEADERS += QxtNamedPipe.h
#unix: SOURCES += QxtNamedPipe_unix.cpp 
