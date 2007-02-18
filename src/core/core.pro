MODULE=QXT_CORE

include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtCore
DEPENDPATH += .
INCLUDEPATH += .

DEFINES += BUILD_QXT_CORE





QT = 



QXT_CORE			+= Nullable
QXT_HEADERS_Nullable 	 	= QxtNull.h QxtNullable.h
QXT_STABILITY_Nullable 	 	= +linux-g++

QXT_CORE			+= SingleInstance
QXT_HEADERS_SingleInstance 	 = QxtSingleInstance.h
QXT_STABILITY_SingleInstance 	 = 

QXT_CORE			+= Tuple
QXT_HEADERS_Tuple  		 = QxtTripple.h QxtTuple.h QxtTupleList.h QxtTypeList.h
QXT_STABILITY_Tuple  		 = +linux-g++

QXT_CORE			+= Pimpl
QXT_HEADERS_Pimpl  		 = QxtPimpl.h
QXT_STABILITY_Pimpl  		 = 


QXT_CORE			+= Error
QXT_HEADERS_Error  		 = QxtError.h
QXT_STABILITY_Error  		 = 

QXT_CORE			+= QxtHyperMacros
QXT_HEADERS_QxtHyperMacros  	 = QxtHyperMacros.h
QXT_STABILITY_QxtHyperMacros     = 
 



include (../parts.pri)

