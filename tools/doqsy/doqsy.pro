TEMPLATE = app
CONFIG -= app_bundle
TARGET =
DESTDIR = ./
DEPENDPATH += .
INCLUDEPATH += .    ../../deploy/include/QxtWeb \
                    ../../src/web \
                    ../../src/core
QT += xml
DEFINES += BUILD_QXT_WEB
SOURCES += main.cpp ../../src/web/qxthtmltemplate.cpp

