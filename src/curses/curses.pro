TARGET 		 =  QxtCurses
DEPENDPATH 	+= .
INCLUDEPATH += . ../core ../../deploy/include
DEFINES 	+= BUILD_QXT_CURSES
CONFIG      += qxtbuild
QT 		     = core
LIBS        += -L../../deploy/libs -lQxtCore -lQxtKit -lpanel -lncurses
TEMPLATE     = lib

QxtCursesApplication.headers     = QxtCursesApplication.h private/QxtCursesApplication_p.h
QxtCursesApplication.interfaces  = QxtCursesApplication
QxtCursesApplication.sources     = QxtCursesApplication.cpp
QxtCursesApplication.stability   =

QxtCPoint.headers                = QxtCPoint.h
QxtCPoint.interfaces             = QxtCPoint
QxtCPoint.sources                = 
QxtCPoint.stability              =

QxtCSize.headers                 = QxtCSize.h
QxtCSize.interfaces              = QxtCSize
QxtCSize.sources                 = 
QxtCSize.stability               =

QxtCRect.headers                 = QxtCRect.h
QxtCRect.interfaces              = QxtCRect
QxtCRect.sources                 =
QxtCRect.stability               =

QxtCKeyEvent.headers             = QxtCKeyEvent.h
QxtCKeyEvent.interfaces          = QxtCKeyEvent
QxtCKeyEvent.sources             =
QxtCKeyEvent.stability           =

QxtCPaintEvent.headers           = QxtCPaintEvent.h
QxtCPaintEvent.interfaces        = QxtCPaintEvent
QxtCPaintEvent.sources           = QxtCPaintEvent.cpp
QxtCPaintEvent.stability         =

QxtCWidget.headers               = QxtCWidget.h
QxtCWidget.interfaces            = QxtCWidget
QxtCWidget.sources               = QxtCWidget.cpp
QxtCWidget.stability             =

QxtCFrame.headers                = QxtCFrame.h
QxtCFrame.interfaces             = QxtCFrame
QxtCFrame.sources                = QxtCFrame.cpp
QxtCFrame.stability              =

Parts = QxtCursesApplication QxtCPoint QxtCSize QxtCRect QxtCKeyEvent QxtCPaintEvent QxtCWidget QxtCFrame

