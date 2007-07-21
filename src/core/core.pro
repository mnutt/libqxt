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



HEADERS += QxtCsvModel.h \
           QxtError.h \
           QxtEventThread.h \
           qxtglobal.h \
           QxtHyperMacros.h \
           qxtmetaobject.h \
           qxtnamespace.h \
           QxtNull.h \
           QxtNullable.h \
           QxtPairList.h \
           qxtpimpl.h \
           QxtSignalWaiter.h \
           QxtSingleInstance.h \
           QxtTuple.h \
           QxtTupleList.h \
           QxtTypeList.h

SOURCES += QxtCsvModel.cpp \
           QxtError.cpp \
           QxtEventThread.cpp \
           qxtmetaobject.cpp \
           QxtSignalWaiter.cpp
