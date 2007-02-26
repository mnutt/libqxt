VERSION 	 =  $$QXVERSION
TEMPLATE 	 =  lib
TARGET 		 =  QxtCore
DEPENDPATH 	+= .
INCLUDEPATH += .
DEFINES 	+= BUILD_QXT_CORE
CONFIG      += qxtbuild
CONFIG      -= qt
QT 		     = 

nullable.headers 	= QxtNull.h QxtNullable.h
nullable.interfaces	= QxtNull QxtNullable
nullable.sources 	=
nullable.stability 	= +linux-g++

SingleInstance.headers	 = QxtSingleInstance.h
SingleInstance.interfaces= QxtSingleInstance
SingleInstance.sources	 =
SingleInstance.stability =

Tuple.headers 		= QxtTripple.h QxtTuple.h QxtTupleList.h QxtTypeList.h
Tuple.interfaces	= QxtTuple QxtTripple
Tuple.sources 		=
Tuple.stability 	= 

Pimpl.headers 		= QxtPimpl.h
Pimpl.interfaces	= QxtPimpl
Pimpl.sources 		=
Pimpl.stability 	= 

Error.headers 		= QxtError.h
Error.interfaces	= QxtError
Error.sources 		=
Error.stability 	= 

HyperMacros.headers 	= QxtHyperMacros.h
HyperMacros.interfaces	= QxtHyperMacros
HyperMacros.sources 	=
HyperMacros.stability 	= 

Parts = nullable SingleInstance Tuple Pimpl Error HyperMacros
