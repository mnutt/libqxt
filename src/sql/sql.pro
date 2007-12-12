include(../../features/qxtfunctions.prf)
TEMPLATE         = lib
CLEAN_TARGET     = QxtSql
TARGET           = $$qxtLibraryTarget($$CLEAN_TARGET)
DESTDIR          = ../../deploy/libs/
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_SQL
win32: CONFIG   += dll
QT               = core sql
QXT              =
INCLUDEPATH     += .
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild
include(../../config.pri)

HEADERS  += qxtsql.h
HEADERS  += qxtsqlpackage.h
HEADERS  += qxtsqlpackagemodel.h

SOURCES  += qxtsqlpackage.cpp
SOURCES  += qxtsqlpackagemodel.cpp
