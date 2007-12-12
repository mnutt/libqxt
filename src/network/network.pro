include(../../features/qxtfunctions.prf)
TEMPLATE         = lib
CLEAN_TARGET     = QxtNetwork
TARGET           = $$qxtLibraryTarget($$CLEAN_TARGET)
DESTDIR          = ../../deploy/libs/
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_NETWORK
win32: CONFIG   += dll
QT               = core network
QXT              = core
INCLUDEPATH     += .
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild
include(../../config.pri)

HEADERS  += qxtnetwork.h
#HEADERS += qxtnamedpipe.h
HEADERS  += qxtrpcpeer.h
           
#SOURCES += qxtnamedpipe.cpp
SOURCES  += qxtrpcpeer.cpp
