MODULE=QXT_CURSES
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtCurses
DEPENDPATH += .
INCLUDEPATH += . ../core ../kit ../../deploy/include
LIBS += -L../../deploy/libs -lQxtCore -lQxtKit -lpanel -lncurses
LIBS += -lpanel -lncurses

QT = core

QXT_CURSES                          += QxtCursesApplication
QXT_HEADERS_QxtCursesApplication     = QxtCursesApplication.h
QXT_SOURCES_QxtCursesApplication     = QxtCursesApplication.cpp
QXT_STABILITY_QxtCursesApplication   =

QXT_CURSES                          += QxtCPoint
QXT_HEADERS_QxtCPoint                = QxtCPoint.h
QXT_SOURCES_QxtCPoint                = 
QXT_STABILITY_QxtCPoint              =

QXT_CURSES                          += QxtCSize
QXT_HEADERS_QxtCSize                 = QxtCSize.h
QXT_SOURCES_QxtCSize                 = 
QXT_STABILITY_QxtCSize               =

QXT_CURSES                          += QxtCRect
QXT_HEADERS_QxtCRect                 = QxtCRect.h
QXT_SOURCES_QxtCRect                 =
QXT_STABILITY_QxtCRect               =

QXT_CURSES                          += QxtCKeyEvent
QXT_HEADERS_QxtCKeyEvent             = QxtCKeyEvent.h
QXT_SOURCES_QxtCKeyEvent             = QxtCKeyEvent.cpp
QXT_STABILITY_QxtCKeyEvent           =

QXT_CURSES                          += QxtCPaintEvent
QXT_HEADERS_QxtCPaintEvent           = QxtCPaintEvent.h
QXT_SOURCES_QxtCPaintEvent           = QxtCPaintEvent.cpp
QXT_STABILITY_QxtCPaintEvent         =

QXT_CURSES                          += QxtCWidget
QXT_HEADERS_QxtCWidget               = QxtCWidget.h
QXT_SOURCES_QxtCWidget               = QxtCWidget.cpp
QXT_STABILITY_QxtCWidget             =

QXT_CURSES                          += QxtCFrame
QXT_HEADERS_QxtCFrame                = QxtCFrame.h
QXT_SOURCES_QxtCFrame                = QxtCFrame.cpp
QXT_STABILITY_QxtCFrame              =

include (../parts.pri)
