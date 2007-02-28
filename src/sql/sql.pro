VERSION          =  $$QXVERSION
TEMPLATE         =  lib
TARGET           =  QxtSql
DEPENDPATH      += .
INCLUDEPATH     += .
DEFINES         += BUILD_QXT_SQL
CONFIG          += qxtbuild convenience
QT               = core sql

INCLUDEPATH     += . ../core ../../deploy/include 
LIBS            += -L../../deploy/libs/ -lQxtKit -lQxtCore



QxtSqlPackage.sources 	= QxtSqlPackage.cpp
QxtSqlPackage.stability = +linux-g++

QxtSqlPackageModel.sources 	= QxtSqlPackageModel.cpp
QxtSqlPackageModel.stability 	= 

Parts=QxtSqlPackage QxtSqlPackageModel
