MODULE=QXT_MEDIA
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtMedia
DEPENDPATH += .
INCLUDEPATH += .
DEFINES += BUILD_QXT_MEDIA
QT = core gui
INCLUDEPATH += . ../core ../../deploy/include
LIBS+=-L../../deploy/libs/ -lQxtKit -lQxtCore




QXT_MEDIA                       += QxtAVFile
QXT_HEADERS_QxtAVFile        	 = QxtAVFile.h private/QxtAVFile_p.h
QXT_SOURCES_QxtAVFile	 	 = QxtAVFile.cpp QxtAVFile_p.cpp
QXT_STABILITY_QxtAVFile      	 =


QXT_MEDIA                       += QxtSdlWidget
QXT_HEADERS_QxtSdlWidget       	 = QxtSdlWidget.h
QXT_SOURCES_QxtSdlWidget 	 = QxtSdlWidget.cpp
QXT_STABILITY_QxtSdlWidgt      	 =

QXT_MEDIA                       += QxtAVPlayer
QXT_HEADERS_QxtAVPlayer          = QxtAVPlayer.h private/QxtAVPlayer_p.h
QXT_SOURCES_QxtAVPlayer 	 = QxtAVPlayer.cpp
QXT_STABILITY_QxtAudioPlayer     =

QXT_MEDIA                       += QxtRingBuffer
QXT_HEADERS_QxtRingBuffer        = QxtRingBuffer.h ringbuffer.h
QXT_SOURCES_QxtRingBuffer 	 = QxtRingBuffer.cpp ringbuffer.c
QXT_STABILITY_QxtRingBuffer      =


LIBS+= -lavcodec -lavformat -lSDL

include (../parts.pri)

QMAKE_CXXFLAGS+= -O2

