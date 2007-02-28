VERSION 	 =  $$QXVERSION
TEMPLATE 	 =  lib
TARGET 		 =  QxtSql
DEPENDPATH 	+= .
INCLUDEPATH     += .
DEFINES 	+= BUILD_QXT_SQL
CONFIG          += qxtbuild
QT 		 = core sql

INCLUDEPATH     += . ../core ../../deploy/include 
LIBS            += -L../../deploy/libs/ -lQxtKit -lQxtCore


QxtSqlPackage.headers 	= QxtSqlPackage.h
QxtSqlPackage.interfaces= QxtSqlPackage
QxtSqlPackage.sources 	= QxtSqlPackage.cpp
QxtSqlPackage.stability = +linux-g++

QxtSqlPackageModel.headers 	= QxtSqlPackageModel.h
QxtSqlPackageModel.interfaces	= QxtSqlPackageModel
QxtSqlPackageModel.sources 	= QxtSqlPackageModel.cpp
QxtSqlPackageModel.stability 	= 

Parts=QxtSqlPackage QxtSqlPackageModel
