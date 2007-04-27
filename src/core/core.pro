TARGET          =  QxtCore
DESTDIR         = ./deploy/libs
DEPENDPATH      += .
INCLUDEPATH     += .
DEFINES         += BUILD_QXT_CORE
win32: CONFIG   += dll
CONFIG          -= qt
QT               = 
INCLUDEPATH     += . ./deploy/include
VERSION          = 0.2.4
TEMPLATE         = lib


HEADERS     =   QxtTypeList.h QxtTupleList.h\
                QxtNull.h\
                QxtNullable.h\
                QxtSingleInstance.h\
                QxtTripple.h\
                QxtTuple.h\
                QxtPimpl.h\
                QxtError.h\
                QxtHyperMacros.h	

SOURCES     =   QxtError.cpp



QXTINSTALLDIR = /usr
include(../../config.pri)
isEmpty(target.path):  target.path   = $${QXTINSTALLDIR}/lib
isEmpty(docs.path):    docs.path     = $${QXTINSTALLDIR}/share/doc/libqxt
isEmpty(include.path): include.path  = $${QXTINSTALLDIR}/include/Qxt
isEmpty(bin.path):     bin.path      = $${QXTINSTALLDIR}/bin


include.files= QxtTypeList.h QxtTupleList.h\
                QxtNull.h\
                QxtNullable.h\
                QxtSingleInstance.h\
                QxtTripple.h\
                QxtTuple.h\
                QxtPimpl.h\
                QxtError.h\
                QxtHyperMacros.h	

include.files+=./deploy/includes/QxtTypeList ./deploy/includes/QxtTupleList \
                ./deploy/includes/QxtNull\
                ./deploy/includes/QxtNullable\
                ./deploy/includes/QxtSingleInstance\
                ./deploy/includes/QxtTripple\
                ./deploy/includes/QxtTuple\
                ./deploy/includes/QxtPimpl\
                ./deploy/includes/QxtError\
                ./deploy/includes/QxtHyperMacros	

INSTALLS = target include

