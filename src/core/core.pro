TARGET = QxtCore
DESTDIR = ../../deploy/libs/
DEPENDPATH += .
INCLUDEPATH += .
DEFINES += BUILD_QXT_CORE
win32: CONFIG += dll
QT = core
INCLUDEPATH += .
TEMPLATE = lib
MOC_DIR = .moc
OBJECTS_DIR = .obj
CONFIG += qxtbuild  convenience
include(../../config.pri)


HEADERS += qxtcsvmodel.h \
           qxterror.h \
           qxtglobal.h \
           qxthypermacros.h \
           qxtmetaobject.h \
           qxtmetatype.h \
           qxtnamespace.h \
           qxtnull.h \
           qxtnullable.h \
           qxtpairList.h \
           qxtpimpl.h \
           qxtsemaphore.h \
           qxtsignalwaiter.h \
           qxttuple.h \
           qxttuplelist.h \
           qxttypelist.h \
           qxtfifo.h \
           qxtstdio.h \
           qxtfilelock_p.h\
           qxtfilelock.h\
           qxtboundfunction.h \
           qxtboundfunctionbase.h \
           qxtboundcfunction.h \
           qxtstdstreambufdevice.h \
           qxtjob.h \
           qxtjob_p.h \
           qxtslotjob.h \
           qxtslotjob_p.h \
           qxtpipe.h \
           qxtdaemon.h \
           qxtlinesocket_p.h \
           qxtlinesocket.h \
           qxtsharedprivate.h 

SOURCES += qxtcsvmodel.cpp \
           qxterror.cpp \
           qxtmetaobject.cpp \
           qxtsemaphore.cpp \
           qxtsignalwaiter.cpp \
           qxtfifo.cpp \
           qxtstdio.cpp\
           qxtfilelock.cpp \
           qxtnull.cpp \
           qxtstdstreambufdevice.cpp \
           qxtjob.cpp \
           qxtslotjob.cpp \
           qxtpipe.cpp \
           qxtdaemon.cpp \
           qxtlinesocket.cpp \
           qxtfilelock_unix.cpp \
           qxtfilelock_win.cpp

