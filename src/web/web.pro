TARGET          =  QxtWeb
DESTDIR         = ../../deploy/libs
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../network
DEFINES         += BUILD_QXT_WEB
win32: CONFIG   += dll
QT               = core network
QXT              = core network
INCLUDEPATH     += .
TEMPLATE         = lib
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONFIG          += qxtbuild convenience
include(../../config.pri)


contains(DEFINES,HAVE_FCGI){
HEADERS += qxtwebfcgiconnector.h qxtwebfcgiconnector_p.h
SOURCES += qxtwebfcgiconnector.cpp
LIBS+=-lfcgi++
}

HEADERS += qxtabstractwebconnector.h \
           qxthtmltemplate.h \
           qxtmail.h \
           qxtsendmail.h \
           qxtwebcontroller.h \
           qxtwebcore.h \
           qxtwebcore_p.h \
           qxtwebhttpconnector.h \
           qxtwebhttpconnector_p.h \
           qxtwebscgiconnector.h \
           qxtwebscgiconnector_p.h \
           qxtwebstatelessconnector.h
SOURCES +=  \
           qxthtmltemplate.cpp \
           qxtmail.cpp \
           qxtsendmail.cpp \
           qxtwebcontroller.cpp \
           qxtwebcore.cpp \
           qxtwebhttpconnector.cpp \
           qxtwebscgiconnector.cpp
