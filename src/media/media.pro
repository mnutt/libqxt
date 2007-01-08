MODULE=QXT_MEDIA
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtMedia
DEPENDPATH += .
INCLUDEPATH += . ..

QT = core


QXT_MEDIA                        += QxtAVFile
QXT_HEADERS_QxtAVFile        	= QxtAVFile.h
QXT_SOURCES_QxtAVFile	 	= QxtAVFile.cpp
QXT_STABILITY_QxtAVFile      	= +linux-g++




include (../parts.pri)

QMAKE_CXXFLAGS+= -O2

