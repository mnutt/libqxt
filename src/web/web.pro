TARGET          =  QxtWeb
#DESTDIR         = .lib
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_WEB
win32: CONFIG   += dll
QT               = core network
QXT              = core
INCLUDEPATH     += .
TEMPLATE         = lib
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONFIG          += qxtbuild convenience


HEADERS += QxtHtmlTemplate.h \
	   QxtScgiApplication.h \
           QxtScgiApplication_p.h \
           QxtScgiController.h 

SOURCES += QxtScgiApplication.cpp QxtHtmlTemplate.cpp  QxtScgiController.cpp
