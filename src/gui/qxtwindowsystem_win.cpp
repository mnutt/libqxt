/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtGui module of the Qxt library.
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtwindowsystem.h"
#include <qt_windows.h>
#include <qglobal.h> // QT_WA

static WindowList qxt_Windows;

BOOL CALLBACK qxt_EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    Q_UNUSED(lParam);
    if (::IsWindowVisible(hwnd))
        qxt_Windows += hwnd;
    return TRUE;
}

WindowList QxtWindowSystem::windows()
{
    qxt_Windows.clear();
    HDESK hdesk = ::OpenInputDesktop(0, FALSE, DESKTOP_READOBJECTS);
    ::EnumDesktopWindows(hdesk, qxt_EnumWindowsProc, 0);
    ::CloseDesktop(hdesk);
    return qxt_Windows;
}

WId QxtWindowSystem::activeWindow()
{
    return ::GetForegroundWindow();
}

WId QxtWindowSystem::findWindow(const QString& title)
{
    QT_WA({
        return ::FindWindow(NULL, (TCHAR*)title.utf16());
    }, {
        return ::FindWindowA(NULL, title.toLocal8Bit());
    });
}

WId QxtWindowSystem::windowAt(const QPoint& pos)
{
    POINT pt;
    pt.x = pos.x();
    pt.y = pos.y();
    return ::WindowFromPoint(pt);
}

QString QxtWindowSystem::windowTitle(WId window)
{
    QString title;
    int len = ::GetWindowTextLength(window);
    if (len >= 0)
    {
        TCHAR* buf = new TCHAR[len+1];
        len = ::GetWindowText(window, buf, len+1);
        QT_WA({
            title = QString::fromUtf16((const ushort*)buf, len);
        }, {
            title = QString::fromLocal8Bit((const char*)buf, len);
        });
        delete[] buf;
    }
    return title;
}

QRect QxtWindowSystem::windowGeometry(WId window)
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
