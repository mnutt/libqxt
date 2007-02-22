MODULE=QXT_NETWORK

include (../../config.pri)


unix {

	LIBS +=  -lssl	
}


win32 {
    INCLUDEPATH +=  "C:\OpenSSL\include\"
    LIBS += "C:\OpenSSL\lib\MinGW\libeay32.a"
    LIBS += "C:\OpenSSL\lib\MinGW\ssleay32.a"
}



VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtNetwork
DEPENDPATH += .
INCLUDEPATH += .
DEFINES += BUILD_QXT_NETWORK
QT = core network

INCLUDEPATH += . ../core ../../deploy/include
LIBS+=-L../../deploy/libs/ -lQxtKit -lQxtCore



QXT_NETWORK                      += QxtBlowFish
QXT_HEADERS_QxtBlowFish           = QxtBlowFish.h
QXT_SOURCES_QxtBlowFish           = QxtBlowFish.cpp
QXT_STABILITY_QxtBlowFish         = +linux-g++ +win32-g++

QXT_NETWORK                      += QxtRPCPeer
QXT_HEADERS_QxtRPCPeer           = QxtRPCPeer.h
QXT_SOURCES_QxtRPCPeer           = QxtRPCPeer.cpp
QXT_STABILITY_QxtRPCPeer         = +linux-g++ +win32-g++



include (../parts.pri)
