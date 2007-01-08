HEADERS += ../../src/media/QxtSdlWidget.h MySdlWidget.h
SOURCES += ../../src/media/QxtSdlWidget.cpp MySdlWidget.cpp main.cpp
INCLUDEPATH += . $$system(sdl-config --cflags | sed -e 's/-I//g')
LIBS += $$system(sdl-config --libs) -lSDL_image
DESTDIR = .
