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
#include <qt_windows.h>

WId QxtDesktopWidget::activeNativeWindow() const
{
	return ::GetForegroundWindow();
}

WId QxtDesktopWidget::findNativeWindow(const QString& title) const
{
	return ::FindWindow(NULL, title.utf16());
}

WId QxtDesktopWidget::nativeWindowAt(const QPoint& pos) const
{
	// TODO: fix me
	HWND res;
	POINT pt;
	pt.x = pos.x();
	pt.y = pos.y();
	return ::WindowFromPoint(pt);
}

QString QxtDesktopWidget::nativeWindowTitle(WId window) const
{
	TCHAR str[256];
	QString title;
	int len = ::GetWindowText(window, str, 256);
	if (len > 0)
		title.setUtf16(str, len);
	return title;
}

QRect QxtDesktopWidget::nativeWindowGeometry(WId window) const
{
	RECT rc;
	QRect rect;
	if (::GetWindowRect(window, &rc))
	{
		rect.setTop(rc.top);
		rect.setBottom(rc.bottom);
		rect.setLeft(rc.left);
		rect.setRight(rc.right);
	}
	return rect;
}
