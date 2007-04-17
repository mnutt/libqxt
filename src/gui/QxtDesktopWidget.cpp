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

/*!
    \class QxtDesktopWidget QxtDesktopWidget
    \ingroup gui
    \brief QxtDesktopWidget provides means for finding certain native windows.

    \note Currently supported platforms are \b X11 and \b Windows.
 */

/*!
    \fn QxtDesktopWidget::activeWindow() const

    Returns a native window system identifier of the active window.

    \note The window is, of course, not necessarily a QWidget.

    Example usage on X11:
    \code
    QxtDesktopWidget desktop;
    WId wid = desktop.activeWindow();
    
    char* name = 0;
    if (XFetchName(QX11Info::display(), wid, &name))
       qDebug() << name; // "Mail - Kontact"
    XFree(name);
    \endcode

    \sa QApplication::activeWindow()
 */

/*!
    \fn QxtDesktopWidget::findWindow(const QString& title) const

    Returns a native window system identifier of the window with given \a title.

    \note The window is, of course, not necessarily a QWidget.

    Example usage on X11:
    \code
    QxtDesktopWidget desktop;
    WId wid = desktop.findWindow("Mail - Kontact");
    XRaiseWindow(QX11Info::display(), wid);
    \endcode

    \sa QWidget::find(WId id)
 */

/*!
    Constructs a new QxtDesktopWidget.
 */
QxtDesktopWidget::QxtDesktopWidget()
{
}

/*!
    Destructs the desktop widget.
 */
QxtDesktopWidget::~QxtDesktopWidget()
{
}
