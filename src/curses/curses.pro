TARGET 		 =  QxtCurses
DEPENDPATH 	+= .
INCLUDEPATH += . ../core ../../deploy/include
DEFINES 	+= BUILD_QXT_CURSES
win32: CONFIG   += dll
CONFIG      += qxtbuild
QT 		     = core
LIBS        += -L../../deploy/libs -lQxtCore -lQxtKit -lpanel -lncurses
TEMPLATE     = lib

QxtCursesApplication.headers     = private/QxtCursesApplication_p.h
QxtCursesApplication.sources     = QxtCursesApplication.cpp

QxtCPaintEvent.sources           = QxtCPaintEvent.cpp
QxtCWidget.sources               = QxtCWidget.cpp
QxtCFrame.sources                = QxtCFrame.cpp

Parts = QxtCursesApplication QxtCPoint QxtCSize QxtCRect QxtCKeyEvent QxtCPaintEvent QxtCWidget QxtCFrame

