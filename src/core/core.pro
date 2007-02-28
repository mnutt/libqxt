VERSION 	 =  $$QXVERSION
TEMPLATE 	 =  lib
TARGET 		 =  QxtCore
DEPENDPATH 	+= .
INCLUDEPATH 	+= .
DEFINES 	+= BUILD_QXT_CORE
CONFIG      	+= qxtbuild convenience
CONFIG      	-= qt
QT 		 = 
INCLUDEPATH     += . ../../deploy/include 


QxtTuple.headers	= QxtTypeList.h QxtTupleList.h


Parts = QxtNull QxtNullable  QxtSingleInstance QxtTripple QxtTuple  QxtPimpl QxtError QxtHyperMacros
