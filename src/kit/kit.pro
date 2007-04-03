TARGET       =  QxtKit
DEPENDPATH 	+= .
INCLUDEPATH += . ../core ../../deploy/include 
DEFINES     += BUILD_QXT_KIT
win32: CONFIG   += dll
CONFIG      += qxtbuild convenience
QT           = core
unix : LIBS        += -L../../deploy/libs/  -lQxtCore
win32: LIBS        += -L../../deploy/libs/  -lQxtCore0
TEMPLATE     = lib

QxtSignalWaiter.sources 	= QxtSignalWaiter.cpp
QxtEventThread.sources 		= QxtEventThread.cpp

Parts = QxtSignalWaiter QxtTrippleList QxtPairList QxtEventThread QxtCsvModel

HEADERS	    +=../../deploy/include/Qxt/qxtnamespace.h
