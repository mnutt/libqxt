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
#ifndef MYSDLWIDGET_H
#define MYSDLWIDGET_H

#include "../../src/media/QxtSdlWidget.h"

class MySdlWidget : public QxtSdlWidget
{
public:
	MySdlWidget(QWidget *parent = 0);
	~MySdlWidget();

	QSize sizeHint() const;

protected:
	void draw(SDL_Surface *sdlSurface);
	void paintEvent(QPaintEvent *paintEvent);

private:
	SDL_Surface *image;
};

#endif // MYSDLWIDGET_H
