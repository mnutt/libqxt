VERSION 	 =  $$QXVERSION
TEMPLATE 	 =  lib
TARGET 		 =  QxtKit
DEPENDPATH 	+= .
INCLUDEPATH += .
DEFINES 	+= BUILD_QXT_KIT
CONFIG      += qxtbuild
QT 		     = core

QxtSignalWaiter.headers 	= QxtSignalWaiter.h
QxtSignalWaiter.interfaces	= QxtSignalWaiter
QxtSignalWaiter.sources 	= QxtSignalWaiter.cpp
QxtSignalWaiter.stability 	= 

QxtTrippleList.headers 		= QxtTrippleList.h
QxtTrippleList.interfaces	= QxtTrippleList
QxtTrippleList.sources 		= 
QxtTrippleList.stability 	= 

QxtPairList.headers 		= QxtPairList.h
QxtPairList.interfaces		= QxtPairList
QxtPairList.sources 		= 
QxtPairList.stability 		= 

QxtEventThread.headers 		= QxtEventThread.h
QxtEventThread.interfaces	= QxtEventThread
QxtEventThread.sources 		= QxtEventThread.cpp
QxtEventThread.stability 	= 

Parts = QxtSignalWaiter QxtTrippleList QxtPairList QxtEventThread

HEADERS	    +=../../deploy/include/Qxt/qxtnamespace.h
