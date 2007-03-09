TARGET           =  QxtCore
DEPENDPATH      += .
INCLUDEPATH     += .
DEFINES         += BUILD_QXT_CORE
win32: CONFIG   += dll
CONFIG          += qxtbuild convenience
CONFIG          -= qt
QT               = 
INCLUDEPATH     += . ../../deploy/include 
TEMPLATE         = lib

QxtTuple.headers        = QxtTypeList.h QxtTupleList.h
QxtError.sources        = QxtError.cpp

Parts = QxtNull QxtNullable  QxtSingleInstance QxtTripple QxtTuple  QxtPimpl QxtError QxtHyperMacros
