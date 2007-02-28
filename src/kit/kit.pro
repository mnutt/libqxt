VERSION 	 =  $$QXVERSION
TEMPLATE 	 =  lib
TARGET 		 =  QxtKit
DEPENDPATH 	+= .
INCLUDEPATH     += .
DEFINES 	+= BUILD_QXT_KIT
CONFIG          += qxtbuild confidence
QT 		 = core
INCLUDEPATH     += . ../core ../../deploy/include 
LIBS            += -L../../deploy/libs/  -lQxtCore



QxtSignalWaiter.sources 	= QxtSignalWaiter.cpp
QxtEventThread.sources 		= QxtEventThread.cpp




Parts = QxtSignalWaiter QxtTrippleList QxtPairList QxtEventThread

HEADERS	    +=../../deploy/include/Qxt/qxtnamespace.h
