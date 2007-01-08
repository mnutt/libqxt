MODULE=QXT_GUI
include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtGui
DEPENDPATH += .
INCLUDEPATH += . ..

QT = core gui


QXT_GUI                         += QxtTreeWidget
QXT_HEADERS_QxtTreeWidget        = QxtTreeWidget.h
QXT_SOURCES_QxtTreeWidget	 = QxtTreeWidget.cpp
QXT_STABILITY_QxtTreeWidget      = +linux-g++




include (../parts.pri)




