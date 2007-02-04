/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Bjoern Erik Nilsen <bjoern.nilsen@bjoernen.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

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
