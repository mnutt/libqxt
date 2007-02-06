MODULE=QXT_GUI
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtGui
DEPENDPATH += .
INCLUDEPATH += . ../core ../../deploy/include
DEFINES += BUILD_QXT_GUI
LIBS+=-L../../deploy/libs/ -lQxtKit



QT = core gui

QXT_GUI                         += QxtLabel
QXT_HEADERS_QxtLabel             = QxtLabel.h
QXT_SOURCES_QxtLabel             = QxtLabel.cpp
QXT_STABILITY_QxtLabel           = +linux-g++

QXT_GUI                         += QxtPushButton
QXT_HEADERS_QxtPushButton        = QxtPushButton.h
QXT_SOURCES_QxtPushButton        = QxtPushButton.cpp
QXT_STABILITY_QxtPushButton      = +linux-g++

QXT_GUI                         += QxtItemDelegate
QXT_HEADERS_QxtItemDelegate      = QxtItemDelegate.h
QXT_SOURCES_QxtItemDelegate      = QxtItemDelegate.cpp
QXT_STABILITY_QxtItemDelegate    = +linux-g++

QXT_GUI                         += QxtTreeWidget
QXT_HEADERS_QxtTreeWidget        = QxtTreeWidget.h QxtTreeWidget_p.h
QXT_SOURCES_QxtTreeWidget        = QxtTreeWidget.cpp
QXT_STABILITY_QxtTreeWidget      = +linux-g++

QXT_GUI                         += QxtTabWidget
QXT_HEADERS_QxtTabWidget         = QxtTabWidget.h
QXT_SOURCES_QxtTabWidget         = QxtTabWidget.cpp
QXT_STABILITY_QxtTabWidget       = +linux-g++

include (../parts.pri)
