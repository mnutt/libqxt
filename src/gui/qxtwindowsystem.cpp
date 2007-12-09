/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtGui module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtwindowsystem.h"
#include <QStringList>

/*!
    \class QxtWindowSystem QxtWindowSystem
    \ingroup QxtGui
    \brief QxtWindowSystem provides means for accessing native windows.

    \note QxtWindowSystem is portable in principle, but be careful while
    using it since you are probably about to do something non-portable.

    <P>Advanced example usage:
    \code
    class NativeWindow : public QWidget {
        public:
            NativeWindow(WId wid) {
                QWidget::create(wid, false, false); // window, initializeWindow, destroyOldWindow
            }
            ~NativeWindow() {
                QWidget::destroy(false, false); // destroyWindow, destroySubWindows
            }
    };
    \endcode

    \code
    WindowList windows = QxtWindowSystem::windows();
    QStringList titles = QxtWindowSystem::windowTitles();
    bool ok = false;
    QString title = QInputDialog::getItem(0, "Choose Window", "Choose a window to be hid:", titles, 0, false, &ok);
    if (ok)
    {
        int index = titles.indexOf(title);
        if (index != -1)
        {
            NativeWindow window(windows.at(index));
            window.hide();
        }
    }
    \endcode

    \note Currently supported platforms are \b X11 and \b Windows.
 */

/*!
    \fn QxtWindowSystem::windows()

    Returns the list of native window system identifiers.

    \note The windows are not necessarily QWidgets.

    \sa QApplication::topLevelWidgets(), windowTitles()
 */


/*!
    \fn QxtWindowSystem::activeWindow()

    Returns the native window system identifier of the active window if any.

    Example usage:
    \code
    WId wid = QxtWindowSystem::activeWindow();
    QString title = QxtWindowSystem::windowTitle(wid);
    qDebug() << "Currently active window is:" << title;
    \endcode

    \note The window is not necessarily a QWidget.

    \sa QApplication::activeWindow()
 */

/*!
    \fn QxtWindowSystem::findWindow(const QString& title)

    Returns the native window system identifier of the window if any with given \a title.

    Example usage:
    \code
    WId wid = QxtWindowSystem::findWindow("Mail - Kontact");
    QPixmap screenshot = QPixmap::grabWindow(wid);
    \endcode

    \note The window is not necessarily a QWidget.

    \sa QWidget::find()
 */

/*!
    \fn QxtWindowSystem::windowAt(const QPoint& pos)

    Returns the native window system identifier of the window if any at \a pos.

    Example usage:
    \code
    QPoint point = // a mouse press or something
    WId wid = QxtWindowSystem::windowAt(point);
    QPixmap screenshot = QPixmap::grabWindow(wid);
    \endcode

    \note The window is not necessarily a QWidget.

    \sa QApplication::widgetAt()
 */

/*!
    \fn QxtWindowSystem::windowTitle(WId window)

    Returns the title of the native \a window.

    Example usage:
    \code
    WId wid = QxtWindowSystem::activeWindow();
    QString title = QxtWindowSystem::windowTitle(wid);
    qDebug() << "Currently active window is:" << title;
    \endcode

    \sa QWidget::windowTitle(), windowTitles()
 */

/*!
    \fn QxtWindowSystem::windowTitles()

    Returns a list of native window titles.

    Example usage:
    \code
    qDebug() << "Windows:";
    foreach (QString title, QxtWindowSystem::windowTitles())
       qDebug() << title;
    \endcode

    \sa QWidget::windowTitle(), windowTitle(), windows()
 */

/*!
    \fn QxtWindowSystem::windowGeometry(WId window)

    Returns the geometry of the native \a window.

    Example usage:
    \code
    WId wid = QxtWindowSystem::activeWindow();
    QRect geometry = QxtWindowSystem::windowGeometry(wid);
    qDebug() << "Geometry of the active window is:" << geometry;
    \endcode

    \sa QWidget::frameGeometry()
 */

QStringList QxtWindowSystem::windowTitles()
{
    WindowList windows = QxtWindowSystem::windows();
    QStringList titles;
    foreach (WId window, windows)
    titles += QxtWindowSystem::windowTitle(window);
    return titles;
}
