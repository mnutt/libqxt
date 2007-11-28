TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .    ../../deploy/include/QxtWeb \
                    ../../src/web \
                    ../../src/core
CONFIG+=debug
QT+=xml
SOURCES += main.cpp ../../src/web/qxthtmltemplate.cpp

