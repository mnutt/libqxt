/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Bjoern Erik Nilsen <bjoern.nilsen@bjoernen.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

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
