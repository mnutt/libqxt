/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtGui module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/
#include "qxtscreen.h"
#include "qxtscreen_p.h"
#include <QDesktopWidget>
#include <QApplication>

/*!
    \class QxtScreen QxtScreen
    \ingroup QxtGui
    \brief QxtScreen provides access to screen settings.

    QxtScreen provides access to screen settings.

    \note Currently supported platforms are X11 and Windows.
 */

QxtScreenPrivate::QxtScreenPrivate() :
    currReso(),
    setReso(),
    availResos(),
    currRate(-1),
    setRate(-1),
    availRates(),
    screen(-1)
{
}

void QxtScreenPrivate::invalidate()
{
    currReso = QSize();
    availResos.clear();

    currRate = -1;
    availRates.clear();
    
    screen = -1;
}

void QxtScreenPrivate::init()
{
    if (screen < 0)
        screen = qApp->desktop()->primaryScreen();

    if (availResos.isEmpty() || !currReso.isValid() || availRates.isEmpty() || currRate < 0)
        init_sys();
}

/*!
    Constructs a new QxtScreen for \a screen.

    \note The primary screen is used if \a screen is \c -1.
 */
QxtScreen::QxtScreen(int screen)
{
    qxt_d().screen = screen;
}

/*!
    Destructs the screen object.
 */
QxtScreen::~QxtScreen()
{
}

/*!
    Returns the screen number.
 */
int QxtScreen::screen() const
{
    const_cast<QxtScreen*>(this)->qxt_d().init();
    return qxt_d().screen;
}

/*!
    Sets the screen number.
 */
void QxtScreen::setScreen(int screen)
{
    qxt_d().invalidate();
    qxt_d().screen = screen;
}

/*!
    Returns the list of available resolutions.

    \sa availableRefreshRates()
 */
QList<QSize> QxtScreen::availableResolutions() const
{
    const_cast<QxtScreen*>(this)->qxt_d().init();
    return qxt_d().availResos;
}

/*!
    Returns the list of available refresh rates for \a resolution.

    \sa availableResolutions()
 */
QList<int> QxtScreen::availableRefreshRates(const QSize& resolution) const
{
    const_cast<QxtScreen*>(this)->qxt_d().init();
    return qxt_d().availRates.values(resolution);
}

/*!
    Returns the current resolution.
 */
QSize QxtScreen::resolution() const
{
    const_cast<QxtScreen*>(this)->qxt_d().init();
    return qxt_d().currReso;
}

/*!
    Sets the \a resolution.

    \note No changes are applied until apply() is called.

    \sa apply()
 */
void QxtScreen::setResolution(const QSize& resolution)
{
    qxt_d().setReso = resolution;
}

/*!
    Returns the current refresh rate.
 */
int QxtScreen::refreshRate() const
{
    const_cast<QxtScreen*>(this)->qxt_d().init();
    return qxt_d().currRate;
}

/*!
    Sets the refresh \a rate.

    \note No changes are applied until apply() is called.

    \sa apply()
 */
void QxtScreen::setRefreshRate(int rate)
{
    qxt_d().setRate = rate;
}

/*!
    Applies the resolution and refresh rate.

    \sa setResolution, setRate()
 */
bool QxtScreen::apply()
{
    qxt_d().init();
    return qxt_d().set(qxt_d().setReso, qxt_d().setRate);
}

/*!
    Reverts the resolution and refresh rate.

    \sa setResolution, setRate()
 */
bool QxtScreen::cancel()
{
    qxt_d().init();
    return qxt_d().set(qxt_d().currReso, qxt_d().currRate);
}
