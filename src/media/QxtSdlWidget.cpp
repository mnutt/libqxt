/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Bjoern Erik Nilsen <bjoern.nilsen@bjoernen.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtSdlWidget.h"

#include <SDL/SDL.h>
#include <QApplication>
#if defined(Q_WS_X11)
#include <X11/Xlib.h>
#include <QX11Info>
#endif

QxtSdlWidget::QxtSdlWidget(QWidget *parent)
	: QWidget(parent),
	  sdlSurface(0),
	  sdlFlags(SDL_DOUBLEBUF | SDL_SWSURFACE)
{
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
	background.setRgb(0, 0, 0, 0);
}

QxtSdlWidget::~QxtSdlWidget()
{
	SDL_Quit();
}

void QxtSdlWidget::setFlags(quint32 flags)
{
	sdlFlags = flags;
}

quint32 QxtSdlWidget::flags() const
{
	return sdlFlags;
}

void QxtSdlWidget::setBackgroundColor(const QColor &color)
{
	if (!color.isValid()) {
		qWarning("QxtSdlWidget::setBackgroundColor: color is not valid");
		return;
	}

	if (color == background)
		return;
	background = color;
}

QColor QxtSdlWidget::backgroundColor() const
{
	return background;	
}

void QxtSdlWidget::resizeEvent(QResizeEvent * /*resizeEvent*/)
{
#if defined(Q_WS_X11)
	QApplication::syncX();
#endif

	// Initialize SDL.
	char windowId[64];
	snprintf(windowId, sizeof(windowId), "SDL_WINDOWID=0x%lx", winId());
	putenv(windowId);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		char error[128] = "QxtSdlWidget: Unable to initialize SDL: ";
		strcat(error, SDL_GetError());
		qFatal(error);	
	}

	if (isFullScreen())
		sdlFlags |= SDL_FULLSCREEN;
	else
		sdlFlags &= ~SDL_FULLSCREEN;
	
	// Set new video mode. 
	// The previously allocated surface is automatically deleted by SDL
	const SDL_VideoInfo* info = SDL_GetVideoInfo();
	sdlSurface = SDL_SetVideoMode(width(), height(), info->vfmt->BitsPerPixel, sdlFlags);
	if (!sdlSurface) {
		char error[128] = "QxtSdlWidget: Unable to set vide mode: ";
		strcat(error, SDL_GetError() );
		qFatal(error);
	}

#if defined(QT_NO_CURSOR)
	SDL_ShowCursor(SDL_DISABLE);
#endif
}

void QxtSdlWidget::paintEvent(QPaintEvent * /*paintEvent*/)
{
	if (!sdlSurface)
		return;

#if defined(Q_WS_X11)
    // Make sure we're not conflicting with drawing from the Qt library
    XSync(QX11Info::display(), false);
#endif

	Uint32 color = SDL_MapRGBA(sdlSurface->format,
	                           Uint8(background.red()),
							   Uint8(background.green()),
							   Uint8(background.blue()),
							   Uint8(background.alpha()));
	SDL_FillRect(sdlSurface, 0, color);
	draw(sdlSurface);
	SDL_Flip(sdlSurface);
}

void QxtSdlWidget::draw(SDL_Surface * /*sdlSurface*/)
{
	// Do nothing by default.
}
