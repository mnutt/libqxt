VERSION 	=  $$QXVERSION
TEMPLATE 	=  lib
TARGET 		=  QxtMedia
DEPENDPATH 	+= .
INCLUDEPATH 	+= .
DEFINES 	+= BUILD_QXT_MEDIA
QT 		=  core gui
INCLUDEPATH 	+= . ../core ../../deploy/include ./private
LIBS		+= -L../../deploy/libs/ -lQxtKit -lQxtCore

LIBS		+= -lavcodec -lavformat -lSDL

QxtAVFile.headers 	= QxtAVFile.h private/QxtAVFile_p.h
QxtAVFile.interfaces	= QxtAVFile
QxtAVFile.sources 	= QxtAVFile.cpp QxtAVFile_p.cpp
QxtAVFile.stability 	= 

QxtSdlWidget.headers 	= QxtSdlWidget.h
QxtSdlWidget.interfaces	= QxtSdlWidget
QxtSdlWidget.sources 	= QxtSdlWidget.cpp
QxtSdlWidget.stability 	= 

QxtAVPlayer.headers 	= QxtAVPlayer.h private/QxtAVPlayer_p.h
QxtAVPlayer.interfaces	= QxtAVPlayer
QxtAVPlayer.sources 	= QxtAVPlayer.cpp
QxtAVPlayer.stability 	= 

QxtRingBuffer.headers 	= QxtRingBuffer.h ringbuffer.h
QxtRingBuffer.interfaces= QxtRingBuffer
QxtRingBuffer.sources 	= QxtRingBuffer.cpp ringbuffer.c
QxtRingBuffer.stability = 



ModuleBuild = $$ModuleStabilityCheck(QxtAVFile QxtSdlWidget QxtAVPlayer QxtRingBuffer)
HEADERS     = $$ModuleHeaders($$ModuleBuild)
SOURCES     = $$ModuleSources($$ModuleBuild)
ModuleBuildDebug($$ModuleBuild)
INSTALLS    = $$ModuleInstall($$ModuleBuild)
