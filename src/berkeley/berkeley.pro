CLEAN_TARGET     = QxtBerkeley
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_BERKELEY
QT               = core
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild
LIBS            += -ldb


include(../../config.pri)



HEADERS += qxtbdb.h 
HEADERS += qxtbdbhash.h

SOURCES += qxtbdb.cpp 
SOURCES += qxtbdbhash.cpp
