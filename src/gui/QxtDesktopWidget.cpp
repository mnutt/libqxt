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
    \brief QxtDesktopWidget provides means for accessing native windows.

    \todo Add notice about QWidget::create()?

    \note Currently supported platforms are \b X11 and \b Windows.
 */

/*!
    \fn QxtDesktopWidget::activeWindow()

    Returns a native window system identifier of the active window.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::activeWindow();
    QString title = QxtDesktopWidget::windowTitle(wid);
    qDebug() << "Currently active window is:" << title;
    \endcode

    \note The window is, of course, not necessarily a QWidget.

    \sa QApplication::activeWindow()
 */

/*!
    \fn QxtDesktopWidget::findWindow(const QString& title)

    Returns a native window system identifier of the window with given \a title.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::findWindow("Mail - Kontact");
    QPixmap screenshot = QPixmap::grabWindow(wid);
    \endcode

    \note The window is, of course, not necessarily a QWidget.

    \sa QWidget::find()
 */

/*!
    \fn QxtDesktopWidget::windowAt(const QPoint& pos)

    Returns a native window system identifier of the window if any at \a pos.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::findWindow("Mail - Kontact");
    QPixmap screenshot = QPixmap::grabWindow(wid);
    \endcode

    \note The window is, of course, not necessarily a QWidget.

    \sa QApplication::widgetAt()
 */

/*!
    \fn QxtDesktopWidget::windowTitle(WId window)

    Returns the title of the native \a window.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::activeWindow();
    QString title = QxtDesktopWidget::windowTitle(wid);
    qDebug() << "Currently active window is:" << title;
    \endcode

    \sa QWidget::windowTitle()
 */

/*!
    \fn QxtDesktopWidget::windowGeometry(WId window)

    Returns the geometry of the native \a window.

    Example usage:
    \code
    WId wid = QxtDesktopWidget::activeWindow();
    QRect geometry = QxtDesktopWidget::windowGeometry(wid);
    qDebug() << "Geometry of the window is:" << geometry;
    \endcode

    \sa QWidget::frameGeometry()
 */
