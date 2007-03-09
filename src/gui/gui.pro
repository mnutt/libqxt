TARGET       = QxtGui
DEPENDPATH  += .
INCLUDEPATH += . ../core ../../deploy/include
DEFINES     += BUILD_QXT_GUI
unix : LIBS        += -L../../deploy/libs/ -lQxtKit  -lQxtCore 
win32: LIBS        += -L../../deploy/libs/ -lQxtKit0 -lQxtCore0

win32: CONFIG   += dll


CONFIG      += qxtbuild convenience
QT           = core gui 
TEMPLATE     = lib

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

QxtCheckComboBox.headers	= private/QxtCheckComboBox_p.h
QxtCheckComboBox.sources	= QxtCheckComboBox.cpp

QxtProxyStyle.sources		= QxtProxyStyle.cpp

QxtStringSpinBox.sources	= QxtStringSpinBox.cpp

Parts=QxtLabel QxtPushButton QxtItemDelegate QxtTreeWidget QxtTreeWidgetItem QxtTabWidget QxtApplication QxtCheckComboBox QxtProxyStyle QxtStringSpinBox
