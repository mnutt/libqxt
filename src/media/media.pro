TARGET           =  QxtMedia
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../../deploy/include ./private
DEFINES         += BUILD_QXT_MEDIA
win32: CONFIG   += dll
CONFIG          += qxtbuild convenience
QT               = core gui
unix : LIBS            += -L../../deploy/libs/ -lQxtCore  -lQxtKit
win32: LIBS            += -L../../deploy/libs/ -lQxtCore0 -lQxtKit0

LIBS            += -lavcodec -lavformat -lSDL
TEMPLATE         = lib

QxtAVFile.headers 	= private/QxtAVFile_p.h
QxtAVFile.sources 	= QxtAVFile.cpp QxtAVFile_p.cpp
QxtAVFile.stability 	= 

QxtSdlWidget.sources 	= QxtSdlWidget.cpp
QxtSdlWidget.stability 	= 

QxtAVPlayer.headers 	=  private/QxtAVPlayer_p.h
QxtAVPlayer.sources 	= QxtAVPlayer.cpp
QxtAVPlayer.stability 	= 

QxtRingBuffer.headers 	= ringbuffer.h
QxtRingBuffer.sources 	= QxtRingBuffer.cpp ringbuffer.c
QxtRingBuffer.stability = 

Parts= QxtAVFile QxtSdlWidget QxtAVPlayer QxtRingBuffer

