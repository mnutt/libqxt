TARGET          =  QxtCore
#DESTDIR         = .lib
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



HEADERS += qxtglobal.h qxtnamespace.h \
           QxtCsvModel.h QxtError.h QxtEventThread.h QxtHyperMacros.h QxtNull.h QxtNullable.h QxtPairList.h QxtPimpl.h  \
           QxtSignalWaiter.h QxtSingleInstance.h  QxtTuple.h QxtTupleList.h QxtTypeList.h

SOURCES += QxtCsvModel.cpp QxtError.cpp QxtEventThread.cpp QxtSignalWaiter.cpp
