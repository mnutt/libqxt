CLEAN_TARGET     = QxtGui
DEPENDPATH      += .
INCLUDEPATH     += . ../core
DEFINES         += BUILD_QXT_GUI
QT               = core gui
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += qxtbuild

win32:LIBS      += -luser32


include(../../config.pri)



HEADERS  += qxtapplication.h
HEADERS  += qxtapplication_p.h
HEADERS  += qxtcheckcombobox.h
HEADERS  += qxtcheckcombobox_p.h
HEADERS  += qxtconfigdialog.h
HEADERS  += qxtconfigdialog_p.h
HEADERS  += qxtconfirmationmessage.h
HEADERS  += qxtdockwidget.h
HEADERS  += qxtgui.h
HEADERS  += qxtgroupbox.h
HEADERS  += qxtheaderview.h
HEADERS  += qxtitemdelegate.h
HEADERS  += qxtitemdelegate_p.h
HEADERS  += qxtlabel.h
HEADERS  += qxtlistwidget.h
HEADERS  += qxtlistwidget_p.h
HEADERS  += qxtlistwidgetitem.h
HEADERS  += qxtnativeeventfilter.h
HEADERS  += qxtprogresslabel.h
HEADERS  += qxtproxystyle.h
HEADERS  += qxtpushbutton.h
HEADERS  += qxtspanslider.h
HEADERS  += qxtspanslider_p.h
HEADERS  += qxtstars.h
HEADERS  += qxtstringspinbox.h
HEADERS  += qxtstringvalidator.h
HEADERS  += qxtstringvalidator_p.h
HEADERS  += qxttablewidget.h
HEADERS  += qxttablewidget_p.h
HEADERS  += qxttablewidgetitem.h
HEADERS  += qxttabwidget.h
HEADERS  += qxttooltip.h
HEADERS  += qxttooltip_p.h
HEADERS  += qxttreewidget.h
HEADERS  += qxttreewidget_p.h
HEADERS  += qxttreewidgetitem.h
HEADERS  += qxtwindowsystem.h

SOURCES  += qxtapplication.cpp
SOURCES  += qxtcheckcombobox.cpp
SOURCES  += qxtconfigdialog.cpp
SOURCES  += qxtconfirmationmessage.cpp
SOURCES  += qxtdockwidget.cpp
SOURCES  += qxtgroupbox.cpp
SOURCES  += qxtheaderview.cpp
SOURCES  += qxtitemdelegate.cpp
SOURCES  += qxtlabel.cpp
SOURCES  += qxtlistwidget.cpp
SOURCES  += qxtlistwidgetitem.cpp
SOURCES  += qxtprogresslabel.cpp
SOURCES  += qxtproxystyle.cpp
SOURCES  += qxtpushbutton.cpp
SOURCES  += qxtspanslider.cpp
SOURCES  += qxtstars.cpp
SOURCES  += qxtstringspinbox.cpp
SOURCES  += qxtstringvalidator.cpp
SOURCES  += qxttablewidget.cpp
SOURCES  += qxttablewidgetitem.cpp
SOURCES  += qxttabwidget.cpp
SOURCES  += qxttooltip.cpp
SOURCES  += qxttreewidget.cpp
SOURCES  += qxttreewidgetitem.cpp
SOURCES  += qxtwindowsystem.cpp

unix:!macx:  SOURCES += qxtapplication_x11.cpp qxtwindowsystem_x11.cpp
macx {
       SOURCES += qxtapplication_mac.cpp
       SOURCES -= qxtwindowsystem.cpp
       HEADERS -= qxtwindowsystem.h
}
win32: SOURCES += qxtapplication_win.cpp qxtwindowsystem_win.cpp
