TARGET 		 =  QxtCurses
DEPENDPATH 	+= .
INCLUDEPATH     += . ../core ../../deploy/include
DEFINES 	+= BUILD_QXT_CURSES
win32: CONFIG   += dll
CONFIG          += qxtbuild
QT 		     = core
LIBS        += -lpanel -lncurses

unix:       += -L../../deploy/libs -lQxtCore  -lQxtKit
win32:      += -L../../deploy/libs -lQxtCore0 -lQxtKit0

TEMPLATE     = lib

QxtCursesApplication.headers     = private/QxtCursesApplication_p.h
QxtCursesApplication.sources     = QxtCursesApplication.cpp

QxtCPaintEvent.sources           = QxtCPaintEvent.cpp
QxtCWidget.sources               = QxtCWidget.cpp
QxtCFrame.sources                = QxtCFrame.cpp

Parts = QxtCursesApplication QxtCPoint QxtCSize QxtCRect QxtCKeyEvent QxtCPaintEvent QxtCWidget QxtCFrame

