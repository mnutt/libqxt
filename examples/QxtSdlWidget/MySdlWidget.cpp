/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/
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
