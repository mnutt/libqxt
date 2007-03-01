TARGET       =  QxtKit
DEPENDPATH 	+= .
INCLUDEPATH += . ../core ../../deploy/include 
DEFINES     += BUILD_QXT_KIT
CONFIG      += qxtbuild convenience
QT           = core
# LIBS        += -L../../deploy/libs/  -lQxtCore

QxtSignalWaiter.sources 	= QxtSignalWaiter.cpp
QxtEventThread.sources 		= QxtEventThread.cpp

Parts = QxtSignalWaiter QxtTrippleList QxtPairList QxtEventThread

HEADERS	    +=../../deploy/include/Qxt/qxtnamespace.h
