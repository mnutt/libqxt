MODULE=QXT_MEDIA
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtMedia
DEPENDPATH += .
INCLUDEPATH += . ..

QT = core gui


QXT_MEDIA                       += QxtAVFile
QXT_HEADERS_QxtAVFile        	 = QxtAVFile.h
QXT_SOURCES_QxtAVFile	 	 = QxtAVFile.cpp
QXT_STABILITY_QxtAVFile      	 = +linux-g++


QXT_MEDIA                       += QxtSdlWidget
QXT_HEADERS_QxtSdlWidget       	 = QxtSdlWidget.h
QXT_SOURCES_QxtSdlWidget 	 = QxtSdlWidget.cpp
QXT_STABILITY_QxtSdlWidgt      	 = +linux-g++

QXT_MEDIA                       += QxtAudioPlayer
QXT_HEADERS_QxtAudioPlayer       = QxtAudioPlayer.h
QXT_SOURCES_QxtAudioPlayer 	 = QxtAudioPlayer.cpp
QXT_STABILITY_QxtAudioPlayer     =


LIBS+= -lavcodec -lavformat -lportaudio -lSoundTouch -lSDL

include (../parts.pri)

QMAKE_CXXFLAGS+= -O2

