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

#ifndef QXTSDLWIDGET_H
#define QXTSDLWIDGET_H

#include <Qxt/qxtglobal.h>
#include <QWidget>

struct SDL_Surface;


/**
\class QxtSdlWidget QxtSdlWidget

\ingroup media

\brief use SDL inside a QWidget

take a look at libqxt/examples/QxtSdlWidget please
*/
class QXT_MEDIA_EXPORT QxtSdlWidget : public QWidget
{
public:
	QxtSdlWidget(QWidget *parent = 0);
	virtual ~QxtSdlWidget();

	void setFlags(quint32 flags);
	quint32 flags() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

protected:
	void resizeEvent(QResizeEvent *resizeEvent);
	void paintEvent(QPaintEvent *paintEvent);
	virtual void draw(SDL_Surface *sdlSurface);

private:
	SDL_Surface *sdlSurface;
	quint32 sdlFlags;
	QColor background;
};

#endif // QXTSDLWIDGET_H
