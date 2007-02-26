VERSION      = $$QXVERSION
TEMPLATE     = lib
TARGET       = QxtCurses
DEPENDPATH  += .
INCLUDEPATH += .
LIBS        += -lpanel -lncurses

QT = core
QXT = core kit

CursesApplication.headers     = QxtCursesApplication.h private/QxtCursesApplication_p.h
CursesApplication.interfaces  = QxtCursesApplication
CursesApplication.sources     = QxtCursesApplication.cpp
CursesApplication.stability   =

CPoint.headers                = QxtCPoint.h
CPoint.interfaces             = QxtCPoint
CPoint.sources                = 
CPoint.stability              =

CSize.headers                 = QxtCSize.h
CSize.interfaces              = QxtCSize
CSize.sources                 = 
CSize.stability               =

CRect.headers                 = QxtCRect.h
CRect.interfaces              = QxtCRect
CRect.sources                 =
CRect.stability               =

CKeyEvent.headers             = QxtCKeyEvent.h
CKeyEvent.interfaces          = QxtCKeyEvent
CKeyEvent.sources             =
CKeyEvent.stability           =

CPaintEvent.headers           = QxtCPaintEvent.h
CPaintEvent.interfaces        = QxtCPaintEvent
CPaintEvent.sources           = QxtCPaintEvent.cpp
CPaintEvent.stability         =

CWidget.headers               = QxtCWidget.h
CWidget.interfaces            = QxtCWidget
CWidget.sources               = QxtCWidget.cpp
CWidget.stability             =

CFrame.headers                = QxtCFrame.h
CFrame.interfaces             = QxtCFrame
CFrame.sources                = QxtCFrame.cpp
CFrame.stability              =

Parts = CursesApplication CPoint CSize CRect CKeyEvent CPaintEvent CWidget CFrame
include (../../features/bottom.prf)

