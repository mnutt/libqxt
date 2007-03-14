TARGET       = QxtGui
DEPENDPATH  += .
INCLUDEPATH += . ../core ../../deploy/include
DEFINES     += BUILD_QXT_GUI
unix : LIBS        += -L../../deploy/libs/ -lQxtKit  -lQxtCore 
win32: LIBS        += -L../../deploy/libs/ -lQxtKit0 -lQxtCore0 -luser32 # user32 required for (Un)RegisterHotKey() used in QxtApplication_win.cpp

win32: CONFIG   += dll


CONFIG      += qxtbuild convenience
QT           = core gui 
TEMPLATE     = lib

QxtApplication.sources		= QxtApplication.cpp
unix:QxtApplication.sources	+= QxtApplication_x11.cpp
win32:QxtApplication.sources	+= QxtApplication_win.cpp

QxtCheckComboBox.headers	= private/QxtCheckComboBox_p.h
QxtCheckComboBox.sources	= QxtCheckComboBox.cpp

QxtItemDelegate.sources		= QxtItemDelegate.cpp

QxtLabel.sources		= QxtLabel.cpp

QxtProxyStyle.sources		= QxtProxyStyle.cpp

QxtPushButton.sources		= QxtPushButton.cpp

QxtSpanSlider.sources		= QxtSpanSlider.cpp

QxtStringSpinBox.sources	= QxtStringSpinBox.cpp

QxtTabWidget.sources		= QxtTabWidget.cpp

QxtTreeWidget.headers		= private/QxtTreeWidget_p.h
QxtTreeWidget.sources		= QxtTreeWidget.cpp

QxtTreeWidgetItem.sources	= QxtTreeWidgetItem.cpp


Parts=QxtApplication QxtCheckComboBox QxtItemDelegate QxtLabel QxtProxyStyle QxtPushButton QxtSpanSlider QxtStringSpinBox QxtTabWidget QxtTreeWidget QxtTreeWidgetItem
