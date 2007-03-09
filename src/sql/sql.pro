VERSION          =  $$QXVERSION
TEMPLATE         =  lib
TARGET           =  QxtSql
DEPENDPATH      += .
INCLUDEPATH     += .
DEFINES         += BUILD_QXT_SQL
win32: CONFIG   += dll
CONFIG          += qxtbuild convenience
QT               = core sql
TEMPLATE     = lib

INCLUDEPATH     += . ../core ../../deploy/include 
LIBS            += -L../../deploy/libs/ -lQxtKit -lQxtCore



QxtSqlPackage.sources 	= QxtSqlPackage.cpp
QxtSqlPackage.stability = +linux-g++

QxtSqlPackageModel.sources 	= QxtSqlPackageModel.cpp
QxtSqlPackageModel.stability 	= 

Parts=QxtSqlPackage QxtSqlPackageModel
