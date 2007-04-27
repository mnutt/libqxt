TARGET       =  QxtKit
DEPENDPATH 	+= .
INCLUDEPATH += . ../core ../../deploy/include 
DEFINES     += BUILD_QXT_KIT
win32: CONFIG   += dll
QT           = core
unix : LIBS        += -L../../deploy/libs/  -lQxtCore
win32: LIBS        += -L../../deploy/libs/  -lQxtCore0
TEMPLATE     = lib





HEADERS	=	QxtSignalWaiter.h QxtEventThread.h QxtCsvModel.h QxtTrippleList.h QxtPairList.h 
SOURCES =	QxtSignalWaiter.cpp QxtEventThread.cpp QxtCsvModel.cpp 




#the moc stuff for the enums will be compiled in here
HEADERS	    +=../../deploy/include/Qxt/qxtnamespace.h
