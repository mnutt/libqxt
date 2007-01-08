/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Bjoern Erik Nilsen <bjoern.nilsen@bjoernen.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "MySdlWidget.h"

#include <SDL/SDL_image.h>
#include <QPainter>

MySdlWidget::MySdlWidget(QWidget *parent)
	: QxtSdlWidget(parent)
{
	image = IMG_Load("nerd.png");
	if (!image)
		qWarning(SDL_GetError());
}

MySdlWidget::~MySdlWidget()
{
	if (image) {
		SDL_FreeSurface(image);
		image = 0;
	}
}

QSize MySdlWidget::sizeHint() const
{
	if (!image)
		return QxtSdlWidget::sizeHint();
	return QSize(image->w + 20, image->h + 50);
}

void MySdlWidget::draw(SDL_Surface *sdlSurface)
{
	if (!image)
		return;

	// Blit the image on to the center of the surface
	SDL_Rect destination;
	destination.x = (sdlSurface->w - image->w) >> 1;
	destination.y = (sdlSurface->h - image->h) >> 1;
	destination.w = image->w;
	destination.h = image->h;
	SDL_BlitSurface(image, 0, sdlSurface, &destination);		

	// Frame around the image
	QPainter painter(this);
	painter.setPen(Qt::gray);
	painter.drawRect(destination.x, destination.y, destination.w, destination.h);
}

void MySdlWidget::paintEvent(QPaintEvent *paintEvent)
{
	QxtSdlWidget::paintEvent(paintEvent);	

	// Text on top
	QPainter painter(this);
	painter.setPen(Qt::gray);
	QLatin1String text("Hi, I'm a nerd!");
	int x = qMax(width() - fontMetrics().width(text), 0) / 2;
	painter.drawText(x, 20, text);
}
