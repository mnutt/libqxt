TARGET           =  QxtCore
DEPENDPATH      += .
INCLUDEPATH     += .
DEFINES         += BUILD_QXT_CORE
win32: CONFIG   += dll
CONFIG          -= qt
QT               = 
INCLUDEPATH     += . ../../deploy/include 
TEMPLATE         = lib

HEADERS   = 	QxtTypeList.h QxtTupleList.h 	\
		QxtNull.h			\
		QxtNullable.h			\
		QxtSingleInstance.h 		\
		QxtTripple.h			\
		QxtTuple.h			\
		QxtPimpl.h			\
		QxtError.h			\
		QxtHyperMacros.h	

SOURCES	=	QxtError.cpp

