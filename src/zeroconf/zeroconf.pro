TEMPLATE         = lib
CLEAN_TARGET     = QxtZeroconf
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../network
unix:!macx:LIBS += -ldns_sd -lavahi-client -lavahi-qt4 -lavahi-common

win32:LIBS        += -L"c:\\PROGRA~1\\BONJOU~1\\lib\\win32" -ldnssd
win32:INCLUDEPATH += "c:\\program files\\bonjour sdk\\include"
DEFINES         += BUILD_QXT_ZEROCONF
QT               = core network
QXT              = core network
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

include(../../config.pri)
include(zeroconf.pri)
