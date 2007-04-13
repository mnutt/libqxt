TARGET           =  QxtNetwork
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../../deploy/include
DEFINES         += BUILD_QXT_NETWORK
win32: CONFIG   += dll
CONFIG          += qxtbuild convenience
QT              =  core network
TEMPLATE        = lib
include (../../config.pri)



unix : LIBS            += -L../../deploy/libs/ -lQxtCore  -lQxtKit
win32: LIBS            += -L../../deploy/libs/ -lQxtCore0 -lQxtKit0




QxtRPCPeer.sources 	= QxtRPCPeer.cpp
QxtRPCPeer.stability 	= +linux-g++ +win32-g++

Parts=QxtRPCPeer


contains(DEFINES,HAVE_OPENSSL){
QxtBlowFish.sources 	= QxtBlowFish.cpp
QxtBlowFish.stability 	= +linux-g++ -win32-g++
Parts+=QxtBlowFish
LIBS            += -lssl	
}
