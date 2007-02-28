VERSION      = $$QXVERSION
TEMPLATE     = lib
TARGET       = QxtGui
DEPENDPATH  += .
INCLUDEPATH += . ../core ../../deploy/include
DEFINES     += BUILD_QXT_GUI
LIBS        += -L../../deploy/libs/ -lQxtKit -lQxtCore
CONFIG      += qxtbuild confidence
QT           = core gui 

QxtLabel.sources		= QxtLabel.cpp

QxtPushButton.sources		= QxtPushButton.cpp

QxtItemDelegate.sources		= QxtItemDelegate.cpp

QxtTreeWidget.headers		= private/QxtTreeWidget_p.h
QxtTreeWidget.sources		= QxtTreeWidget.cpp

QxtTreeWidgetItem.sources	= QxtTreeWidgetItem.cpp

QxtTabWidget.sources		= QxtTabWidget.cpp

QxtApplication.sources		= QxtApplication.cpp
unix:QxtApplication.sources	+= QxtApplication_x11.cpp
win32:QxtApplication.sources	+= QxtApplication_win.cpp

QxtCheckComboBox.sources	= QxtCheckComboBox.cpp

Parts=QxtLabel QxtPushButton QxtItemDelegate QxtTreeWidget QxtTreeWidgetItem QxtTabWidget QxtApplication QxtCheckComboBox
