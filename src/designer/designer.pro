CLEAN_TARGET     = QxtDesignerPlugins
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../gui
QT               = core gui
QXT              = core gui
CONVENIENCE     += $$CLEAN_TARGET
CONFIG          += designer plugin qxtbuild
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
include(../../config.pri)


HEADERS  += qxtcheckcomboboxplugin.h
HEADERS  += qxtdesignerplugin.h
HEADERS  += qxtdesignerplugins.h
HEADERS  += qxtgroupboxplugin.h
HEADERS  += qxtlabelplugin.h
HEADERS  += qxtlistwidgetplugin.h
HEADERS  += qxtprogresslabelplugin.h
HEADERS  += qxtpushbuttonplugin.h
HEADERS  += qxtspansliderplugin.h
HEADERS  += qxtstarsplugin.h
HEADERS  += qxtstringspinboxplugin.h
HEADERS  += qxttablewidgetplugin.h
HEADERS  += qxttreewidgetplugin.h

SOURCES  += qxtcheckcomboboxplugin.cpp
SOURCES  += qxtdesignerplugin.cpp
SOURCES  += qxtdesignerplugins.cpp
SOURCES  += qxtgroupboxplugin.cpp
SOURCES  += qxtlabelplugin.cpp
SOURCES  += qxtlistwidgetplugin.cpp
SOURCES  += qxtprogresslabelplugin.cpp
SOURCES  += qxtpushbuttonplugin.cpp
SOURCES  += qxtspansliderplugin.cpp
SOURCES  += qxtstarsplugin.cpp
SOURCES  += qxtstringspinboxplugin.cpp
SOURCES  += qxttablewidgetplugin.cpp
SOURCES  += qxttreewidgetplugin.cpp

RESOURCES += resources.qrc
