CLEAN_TARGET     = QxtBerkeley
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_BERKELEY
QT               = core
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild
LIBS            += -ldb
TEMPLATE         = lib

include(../../config.pri)



HEADERS += qxtbdb.h 
HEADERS += qxtbdbhash.h
HEADERS += qxtbdbtree.h

SOURCES += qxtbdb.cpp 
SOURCES += qxtbdbhash.cpp
SOURCES += qxtbdbtree.cpp 
