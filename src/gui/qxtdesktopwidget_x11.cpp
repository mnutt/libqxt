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
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/


#include "qxtdesktopwidget.h"
#include <QX11Info>
#include <X11/Xutil.h>

WId QxtDesktopWidget::activeWindow()
{
	Window focus;
	int revert = 0;
	Display* display = QX11Info::display();
	XGetInputFocus(display, &focus, &revert);
	return focus;
}

static WId qxt_findWindowHelper(WId wid, const QString& title)
{
	Window root;
	Window parent;
	uint count = 0;
	Window* children = 0;
	Display* display = QX11Info::display();
	if (XQueryTree(display, wid, &root, &parent, &children, &count))
	{
		for (uint i = 0; i < count; ++i)
		{
			if (QxtDesktopWidget::windowTitle(children[i]) == title)
			{
				XFree(children);
				return children[i];
			}
			
			Window window = qxt_findWindowHelper(children[i], title);
			if (window)
			{
				XFree(children);
				return window;
			}
		}
	}
	XFree(children);
	return 0;
}

WId QxtDesktopWidget::findWindow(const QString& title)
{
	return qxt_findWindowHelper(QX11Info::appRootWindow(), title);
}

WId QxtDesktopWidget::windowAt(const QPoint& pos)
{
	// XQueryTree + XGetGeometry ???
	Q_UNUSED(pos);
	return 0;
}

QString QxtDesktopWidget::windowTitle(WId window)
{
	QString name;
	char* str = 0;
	if (XFetchName(QX11Info::display(), window, &str))
	{
		name = QString::fromLatin1(str);
	}
	XFree(str);
	return name;
}

QRect QxtDesktopWidget::windowGeometry(WId window)
{
	QRect rect;
	int x = 0;
	int y = 0;
	uint width = 0;
	uint height = 0;
	uint depth = 0;
	uint border = 0;
	Window root;
	Display* display = QX11Info::display();
	if (XGetGeometry(display, window, &root, &x, &y, &width, &height, &border, &depth))
	{
		rect = QRect(x, y, width, height);
	}
	return rect;
}
