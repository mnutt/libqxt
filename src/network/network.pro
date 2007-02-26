VERSION 	 =  $$QXVERSION
TEMPLATE 	 =  lib
TARGET 		 =  QxtNetwork
DEPENDPATH 	+= .
INCLUDEPATH += . ../core ../../deploy/include
DEFINES 	+= BUILD_QXT_NETWORK
CONFIG      += qxtbuild
QT 		     =  core network

LIBS        += -L../../deploy/libs/ -lQxtKit -lQxtCore 
LIBS        += -lssl	

QxtBlowFish.headers 	= QxtBlowFish.h
QxtBlowFish.interfaces	= QxtBlowFish
QxtBlowFish.sources 	= QxtBlowFish.cpp
QxtBlowFish.stability 	= +linux-g++ +win32-g++


QxtRPCPeer.headers 	= QxtRPCPeer.h
QxtRPCPeer.interfaces	= QxtRPCPeer
QxtRPCPeer.sources 	= QxtRPCPeer.cpp
QxtRPCPeer.stability 	= +linux-g++ +win32-g++

Parts=QxtBlowFish QxtRPCPeer
