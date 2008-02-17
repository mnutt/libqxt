TEMPLATE = app
TARGET =
QT += xml
DESTDIR = ./
DEPENDPATH += .
INCLUDEPATH += .    ../../deploy/include/QxtWeb \
                    ../../src/web \
                    ../../src/core
SOURCES += ../../src/web/qxthtmltemplate.cpp

HEADERS += assistant.h html.h output.h parser.h doxygen.h
SOURCES += assistant.cpp doxygen.cpp html.cpp output.cpp main.cpp 



