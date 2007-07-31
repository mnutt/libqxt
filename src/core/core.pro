TARGET           = QxtCore
DESTDIR          = ../../deploy/libs/
DEPENDPATH      += .
INCLUDEPATH     += .
DEFINES         += BUILD_QXT_CORE
win32: CONFIG   += dll
QT               = core
INCLUDEPATH     += .
TEMPLATE         = lib
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONFIG += qxtbuild  convenience


HEADERS += qxtcsvmodel.h \
           qxterror.h \
           qxtglobal.h \
           qxthypermacros.h \
           qxtmetaobject.h \
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
           qxtstdio.h
SOURCES += qxtcsvmodel.cpp \
           qxterror.cpp \
           qxtmetaobject.cpp \
           qxtsemaphore.cpp \
           qxtsignalwaiter.cpp \
           qxtfifo.cpp \
           qxtstdio.cpp
