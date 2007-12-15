CLEAN_TARGET     = QxtSql
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_SQL
QT               = core sql
QXT              =
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)




HEADERS  += qxtsql.h
HEADERS  += qxtsqlpackage.h
HEADERS  += qxtsqlpackagemodel.h

SOURCES  += qxtsqlpackage.cpp
SOURCES  += qxtsqlpackagemodel.cpp
