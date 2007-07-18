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

HEADERS += qxtapplication.h \
           qxtcheckcombobox.h \
           qxtcheckcombobox_p.h \
           qxtconfigdialog.h \
           qxtconfigdialog_p.h \
           qxtconfirmationmessage.h \
           qxtdesktopwidget.h \
           qxtdockwidget.h \
           qxtgroupbox.h \
           qxtheaderview.h \
           qxtitemdelegate.h \
           qxtlabel.h \
           qxtlistwidget.h \
           qxtlistwidget_p.h \
           qxtlistwidgetitem.h \
           qxtprogresslabel.h \
           qxtproxystyle.h \
           qxtpushbutton.h \
           qxtspanslider.h \
           qxtstars.h \
           qxtstringspinbox.h \
           qxttablewidget.h \
           qxttablewidget_p.h \
           qxttablewidgetitem.h \
           qxttabwidget.h \
           qxttooltip.h \
           qxttooltip_p.h \
           QxtTreeWidget.h \
           QxtTreeWidget_p.h \
           QxtTreeWidgetItem.h
SOURCES += qxtapplication.cpp \
           qxtcheckcombobox.cpp \
           qxtconfigdialog.cpp \
           qxtconfirmationmessage.cpp \
           qxtdesktopwidget.cpp \
           qxtdockwidget.cpp \
           qxtgroupbox.cpp \
           qxtheaderview.cpp \
           qxtitemdelegate.cpp \
           qxtlabel.cpp \
           qxtlistwidget.cpp \
           qxtlistwidgetitem.cpp \
           qxtprogresslabel.cpp \
           qxtproxystyle.cpp \
           qxtpushbutton.cpp \
           qxtspanslider.cpp \
           qxtstars.cpp \
           qxtstringspinbox.cpp \
           qxttablewidget.cpp \
           qxttablewidgetitem.cpp \
           qxttabwidget.cpp \
           qxttooltip.cpp \
           qxttreewidget.cpp \
           qxttreewidgetItem.cpp

unix:  SOURCES += qxtdesktopwidget_x11.cpp   qxtapplication_x11.cpp
macx:  SOURCES -= qxtdesktopwidget_x11.cpp   qxtapplication_x11.cpp
macx:  SOURCES += qxtapplication_mac.cpp
win32: SOURCES += qxtdesktopwidget_win.cpp   qxtapplication_win.cpp
