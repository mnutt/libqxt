TARGET          =  QxtWeb
#DESTDIR         = .lib
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_WEB
win32: CONFIG   += dll
QT               = core network
INCLUDEPATH     += .
TEMPLATE         = lib
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONFIG += qxtbuild  convenience


HEADERS += QxtHtmlTemplate.h \
           QxtWebApplication.h \
           QxtWebApplication_p.h \
           QxtWebCommunicator.h \
           QxtWebInternal.h \
           QxtWebSession.h \
           QxtWebWidget.h
SOURCES += QxtHtmlTemplate.cpp \
           QxtWebApplication.cpp \
           QxtWebCommunicator.cpp \
           QxtWebInternal.cpp \
           QxtWebSession.cpp \
           QxtWebWidget.cpp
