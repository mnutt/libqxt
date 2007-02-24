VERSION 	= $$QXVERSION
TEMPLATE 	= lib
TARGET 		= QxtKit
DEPENDPATH 	+= .
INCLUDEPATH 	+= .
DEFINES 	+= BUILD_QXT_KIT
QT 		= core


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


Parts = QxtSignalWaiter QxtTrippleList QxtPairList
include (../../features/bottom.prf)



HEADERS	    +=../../deploy/include/Qxt/qxtnamespace.h
