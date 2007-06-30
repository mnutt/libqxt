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

HEADERS += QxtBlowFish.h QxtNamedPipe.h QxtRPCPeer.h
SOURCES += QxtBlowFish.cpp QxtRPCPeer.cpp
unix: SOURCES += QxtNamedPipe_unix.cpp 
