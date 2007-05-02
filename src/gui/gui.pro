TARGET       = QxtGui
DEPENDPATH  += .
INCLUDEPATH += . ../core ../../deploy/include
DEFINES     += BUILD_QXT_GUI
unix : LIBS        += -L../../deploy/libs/ -lQxtKit  -lQxtCore 
win32: LIBS        += -L../../deploy/libs/ -lQxtKit0 -lQxtCore0 -luser32 # user32 required for (Un)RegisterHotKey() and GetActiveWindow()

win32: CONFIG   += dll


CONFIG      += qxtbuild convenience staticlib
QT           = core gui 
TEMPLATE     = lib

QxtApplication.sources		= QxtApplication.cpp
#unix:QxtApplication.sources	+= QxtApplication_x11.cpp
QxtApplication.sources	+= QxtApplication_win.cpp

QxtCheckComboBox.headers	= private/QxtCheckComboBox_p.h
QxtCheckComboBox.sources	= QxtCheckComboBox.cpp

#QxtDesktopWidget.sources	+= QxtDesktopWidget.cpp
#unix:QxtDesktopWidget.sources	+= QxtDesktopWidget_x11.cpp
#QxtDesktopWidget.sources	+= QxtDesktopWidget_win.cpp

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


QxtHeaderView.sources =  QxtHeaderView.cpp


Parts=QxtApplication QxtCheckComboBox QxtDesktopWidget QxtHeaderView QxtItemDelegate QxtLabel QxtProxyStyle QxtPushButton QxtSpanSlider QxtStringSpinBox QxtTabWidget QxtTreeWidget QxtTreeWidgetItem 
