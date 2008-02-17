TEMPLATE = app
TARGET =
DESTDIR = ./
DEPENDPATH += .
INCLUDEPATH += .    ../../deploy/include/QxtWeb \
                    ../../src/web \
                    ../../src/core
QT += xml
SOURCES += main.cpp ../../src/web/qxthtmltemplate.cpp

