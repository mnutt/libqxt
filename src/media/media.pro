TARGET           =  QxtMedia
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../../deploy/include ./private
DEFINES         += BUILD_QXT_MEDIA
win32: CONFIG   += dll
CONFIG          += qxtbuild convenience
QT               = core gui
unix : LIBS            += -L../../deploy/libs/ -lQxtCore  -lQxtKit
win32: LIBS            += -L../../deploy/libs/ -lQxtCore0 -lQxtKit0

TEMPLATE         = lib

DEFINES+=HAVE_SPEEX OUTSIDE_SPEEX RANDOM_PREFIX=inside_libqxt



contains(DEFINES,HAVE_SDL){
QxtAVPlayer.headers 	=  private/QxtAVPlayer_p.h
QxtAVPlayer.sources 	= QxtAVPlayer.cpp
QxtAVPlayer.stability 	= 
Parts+= QxtAVPlayer
}


QxtRingBuffer.headers 	= ringbuffer.h
QxtRingBuffer.sources 	= QxtRingBuffer.cpp ringbuffer.c resample/resample.c
QxtRingBuffer.stability = 

Parts=QxtRingBuffer




contains(DEFINES,HAVE_SDL){
QxtSdlWidget.sources    = QxtSdlWidget.cpp
QxtSdlWidget.stability  =
LIBS            +=  -lSDL
Parts+= QxtSdlWidget 
}


contains(DEFINES,HAVE_FFMPEG){
QxtAVFile.headers 	= private/QxtAVFile_p.h
QxtAVFile.sources 	= QxtAVFile.cpp QxtAVFile_p.cpp
QxtAVFile.stability 	= 	
Parts+= QxtAVFile
LIBS            += -lavcodec -lavformat
}
