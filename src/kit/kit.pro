VERSION 	= $$QXVERSION
TEMPLATE 	= lib
TARGET 		= QxtKit
DEPENDPATH 	+= .
INCLUDEPATH 	+= .
DEFINES 	+= BUILD_QXT_KIT
QT 		= core

.headers 	= 
.interfaces	= 
.sources 	= 
.stability 	= 

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


ModuleBuild = $$ModuleStabilityCheck(QxtSignalWaiter QxtTrippleList QxtPairList)
HEADERS     = $$ModuleHeaders($$ModuleBuild)
SOURCES     = $$ModuleSources($$ModuleBuild)
ModuleBuildDebug($$ModuleBuild)
INSTALLS    = $$ModuleInstall($$ModuleBuild)




HEADERS	    +=../../deploy/include/Qxt/qxtnamespace.h
