MODULE=QXT_SQL
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtSql
DEPENDPATH += .
INCLUDEPATH += . ..

QT = core sql


HEADERS += 	QxtSqlPackage.h \
		QxtSqlPackageModel.h 


SOURCES += 	QxtSqlPackage.cpp \
		QxtSqlPackageModel.cpp




QXT_SQL                         += QxtSqlPackage
QXT_HEADERS_QxtSqlPackage        = QxtSqlPackage.h
QXT_SOURCES_QxtSqlPackage        = QxtSqlPackage.cpp
QXT_STABILITY_QxtSqlPackage      = +linux-g++

QXT_SQL                         += QxtSqlPackageModel
QXT_HEADERS_QxtSqlPackageModel   = QxtSqlPackageModel.h
QXT_SOURCES_QxtSqlPackageModel   = QxtSqlPackageModel.cpp
QXT_STABILITY_QxtSqlPackageModel =


include (../parts.pri)

