HEADERS += MySdlWidget.h
SOURCES += MySdlWidget.cpp main.cpp
CONFIG += qxt
QXT += media
INCLUDEPATH += . $$system(sdl-config --cflags | sed -e 's/-I//g')
LIBS += $$system(sdl-config --libs) -lSDL_image
DESTDIR = .
