CLEAN_TARGET     = QxtNetwork
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_NETWORK
QT               = core network
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)






HEADERS  += qxtnetwork.h
#HEADERS += qxtnamedpipe.h
HEADERS  += qxtrpcpeer.h
           
#SOURCES += qxtnamedpipe.cpp
SOURCES  += qxtrpcpeer.cpp
