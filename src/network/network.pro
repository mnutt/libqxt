VERSION          =  $$QXVERSION
TEMPLATE         =  lib
TARGET           =  QxtNetwork
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../../deploy/include
DEFINES         += BUILD_QXT_NETWORK
CONFIG          += qxtbuild confidence
QT              =  core network

LIBS            += -L../../deploy/libs/ -lQxtKit -lQxtCore 
LIBS            += -lssl	


QxtBlowFish.sources 	= QxtBlowFish.cpp
QxtBlowFish.stability 	= +linux-g++ +win32-g++

QxtRPCPeer.sources 	= QxtRPCPeer.cpp
QxtRPCPeer.stability 	= +linux-g++ +win32-g++

Parts=QxtBlowFish QxtRPCPeer
