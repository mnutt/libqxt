include(../../features/qxtfunctions.prf)
TEMPLATE         = lib
CLEAN_TARGET     = QxtWeb
TARGET           = $$qxtLibraryTarget($$CLEAN_TARGET)
DESTDIR          = ../../deploy/libs/
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../network
DEFINES         += BUILD_QXT_WEB
win32: CONFIG   += dll
QT               = core network
QXT              = core network
INCLUDEPATH     += .
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild
include(../../config.pri)

HEADERS  += qxtabstractwebconnector.h
HEADERS  += qxthtmltemplate.h
HEADERS  += qxtmail.h
HEADERS  += qxtsendmail.h
HEADERS  += qxtweb.h
HEADERS  += qxtwebcontroller.h
HEADERS  += qxtwebcore.h
HEADERS  += qxtwebcore_p.h
HEADERS  += qxtwebhttpconnector.h
HEADERS  += qxtwebhttpconnector_p.h
HEADERS  += qxtwebscgiconnector.h
HEADERS  += qxtwebscgiconnector_p.h
HEADERS  += qxtwebstatelessconnector.h

SOURCES  += qxthtmltemplate.cpp
SOURCES  += qxtmail.cpp
SOURCES  += qxtsendmail.cpp
SOURCES  += qxtwebcontroller.cpp
SOURCES  += qxtwebcore.cpp
SOURCES  += qxtwebhttpconnector.cpp
SOURCES  += qxtwebscgiconnector.cpp

contains(DEFINES,HAVE_FCGI){
    HEADERS += qxtwebfcgiconnector.h qxtwebfcgiconnector_p.h
    SOURCES += qxtwebfcgiconnector.cpp
    LIBS+=-lfcgi++
}
