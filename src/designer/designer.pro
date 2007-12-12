include(../../features/qxtfunctions.prf)
TEMPLATE         = lib
CLEAN_TARGET     = QxtDesignerPlugins
TARGET           = $$qxtLibraryTarget($$CLEAN_TARGET)
DEPENDPATH      += .
INCLUDEPATH     += . ../core ../gui
win32: CONFIG   += dll
QT               = core gui
QXT              = core gui
INCLUDEPATH     += .
MOC_DIR          = .moc
OBJECTS_DIR      = .obj
CONFIG          += designer plugin qxtbuild
include(../../config.pri)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

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
