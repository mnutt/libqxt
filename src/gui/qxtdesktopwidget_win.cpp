/****************************************************************************
**
** Copyright (C) J-P Nurmi <jpnurmi@gmail.com>. Some rights reserved.
**
** This file is part of the QxtGui module of the
** Qt eXTension library <http://libqxt.sourceforge.net>
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "qxtdesktopwidget.h"
#include <qt_windows.h>

static WindowList qxt_Windows;

BOOL CALLBACK qxt_EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	Q_UNUSED(lParam);
	if (::IsWindowVisible(hwnd))
		qxt_Windows += hwnd;
	return TRUE;
}

WindowList QxtDesktopWidget::windows()
{
	qxt_Windows.clear();
	HDESK hdesk = ::OpenInputDesktop(0, FALSE, DESKTOP_READOBJECTS);
	::EnumDesktopWindows(hdesk, qxt_EnumWindowsProc, 0);
	::CloseDesktop(hdesk);
	return qxt_Windows;
}

WId QxtDesktopWidget::activeWindow()
{
	return ::GetForegroundWindow();
}

WId QxtDesktopWidget::findWindow(const QString& title)
{
	std::wstring str = title.toStdWString();
	return ::FindWindow(NULL, str.c_str());
}

WId QxtDesktopWidget::windowAt(const QPoint& pos)
{
	POINT pt;
	pt.x = pos.x();
	pt.y = pos.y();
	return ::WindowFromPoint(pt);
}

QString QxtDesktopWidget::windowTitle(WId window)
{
	QString title;
	int len = ::GetWindowTextLength(window);
	if (len >= 0)
	{
		wchar_t* buf = new wchar_t[len+1];
		len = ::GetWindowText(window, buf, len+1);
		title = QString::fromStdWString(std::wstring(buf, len));
		delete[] buf;
	}
	return title;
}

QRect QxtDesktopWidget::windowGeometry(WId window)
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
