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


#include "QxtDesktopWidget.h"
#include <QX11Info>
#include <X11/Xutil.h>

WId QxtDesktopWidget::activeWindow() const
{
//	XGetInputFocus(display, focus_return, revert_to_return)
//		Display *display;
//		Window *focus_return;
//		int *revert_to_return;
	
	Window focus;
	int revert = 0;
	Display* display = QX11Info::display();
	XGetInputFocus(display, &focus, &revert);
	return focus;
}

static WId qxt_findWindowHelper(WId wid, const QString& title)
{
//	Status XQueryTree(display, w, root_return, parent_return, children_return, nchildren_return)
//		Display *display;
//		Window w;
//		Window *root_return;
//		Window *parent_return;
//		Window **children_return;
//		unsigned int *nchildren_return;
	
	Window root;
	Window parent;
	uint count = 0;
	Window* children = 0;
	Display* display = QX11Info::display();
	if (XQueryTree(display, wid, &root, &parent, &children, &count))
	{
		for (uint i = 0; i < count; ++i)
		{
			Window window = qxt_findWindowHelper(children[i], title);
			if (window)
				return window;
			
			char* name = 0;
			if (XFetchName(display, children[i], &name))
			{
				if (title == name)
				{
					XFree(name);
					return children[i];
				}
			}
			XFree(name);
		}
	}
	XFree(children);
	return 0;
}

WId QxtDesktopWidget::findWindow(const QString& title) const
{
	return qxt_findWindowHelper(QX11Info::appRootWindow(), title);
}

WId QxtDesktopWidget::windowAt(const QPoint& pos) const
{
	// XQueryTree + XGetGeometry ???
}

QRect QxtDesktopWidget::windowGeometry(WId window) const
{
	// XGetGeometry
}
