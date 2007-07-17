TARGET           = QxtGui
DESTDIR          = ../../deploy/libs/
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_GUI
win32: CONFIG   += dll
QT               = core gui
QXT              = core
INCLUDEPATH     += . 
TEMPLATE         = lib
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONFIG          += qxt qxtbuild convenience

HEADERS += QxtApplication.h QxtCheckComboBox.h QxtCheckComboBox_p.h QxtDesktopWidget.h QxtHeaderView.h  \
           QxtItemDelegate.h QxtLabel.h QxtProxyStyle.h QxtPushButton.h QxtSpanSlider.h QxtStringSpinBox.h  \
           QxtTabWidget.h QxtTreeWidget.h QxtTreeWidget_p.h QxtTreeWidgetItem.h
SOURCES += QxtApplication.cpp  QxtCheckComboBox.cpp QxtDesktopWidget.cpp \
           QxtHeaderView.cpp  QxtItemDelegate.cpp QxtLabel.cpp QxtProxyStyle.cpp QxtPushButton.cpp  \
           QxtSpanSlider.cpp QxtStringSpinBox.cpp QxtTabWidget.cpp QxtTreeWidget.cpp QxtTreeWidgetItem.cpp 

unix:  SOURCES += QxtDesktopWidget_x11.cpp   QxtApplication_x11.cpp
macx:  SOURCES -= QxtDesktopWidget_x11.cpp   QxtApplication_x11.cpp
macx:  SOURCES += QxtApplication_mac.cpp
win32: SOURCES += QxtDesktopWidget_win.cpp   QxtApplication_win.cpp
