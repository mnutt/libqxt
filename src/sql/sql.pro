VERSION 	= $$QXVERSION
TEMPLATE 	= lib
TARGET 		= QxtSql
DEPENDPATH 	+= .
INCLUDEPATH 	+= .
DEFINES 	+= BUILD_QXT_SQL
QT 		= core sql


QxtSqlPackage.headers 	= QxtSqlPackage.h
QxtSqlPackage.interfaces= QxtSqlPackage
QxtSqlPackage.sources 	= QxtSqlPackage.cpp
QxtSqlPackage.stability = +linux-g++

QxtSqlPackageModel.headers 	= QxtSqlPackageModel.h
QxtSqlPackageModel.interfaces	= QxtSqlPackageModel
QxtSqlPackageModel.sources 	= QxtSqlPackageModel.cpp
QxtSqlPackageModel.stability 	= 



ModuleBuild = $$ModuleStabilityCheck(QxtSqlPackage QxtSqlPackageModel)
HEADERS     = $$ModuleHeaders($$ModuleBuild)
SOURCES     = $$ModuleSources($$ModuleBuild)
ModuleBuildDebug($$ModuleBuild)
INSTALLS    = $$ModuleInstall($$ModuleBuild)