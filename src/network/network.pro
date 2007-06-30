TARGET          =  QxtNetwork
DESTDIR         = .lib
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_NETWORK
win32: CONFIG   += dll
QT               = core network
INCLUDEPATH     += .
VERSION          = 0.2.4
TEMPLATE         = lib
MOC_DIR          = .moc
OBJECTS_DIR      = .obj

HEADERS += QxtBlowFish.h QxtNamedPipe.h QxtRPCPeer.h
SOURCES += QxtBlowFish.cpp QxtRPCPeer.cpp
unix: SOURCES += QxtNamedPipe_unix.cpp 
