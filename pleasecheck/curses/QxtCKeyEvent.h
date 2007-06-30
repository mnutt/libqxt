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
#ifndef QXTCKEYEVENT_H
#define QXTCKEYEVENT_H

#include <QEvent>

/*!
 * \class QxtCKeyEvent
 * \ingroup curses
 * \brief Describes a keyboard input event
 *
 * The QxtCKeyEvent class describes a keyboard input event.
 */
class QxtCKeyEvent : public QEvent {
public:
    /*!
     * Creates a new QxtCKeyEvent.
     *
     * The qtKey values can be found in the Qt::Key enum. It may be Qt::Key_unknown, meaning
     * that the ncurses key code (passed via rawKey) could not be mapped to a Qt key code.
     */
    QxtCKeyEvent(int qtKey, Qt::KeyboardModifiers mods = Qt::NoModifier, int rawKey = 0)
        : QEvent(QEvent::KeyPress), v(qtKey), k(rawKey), m(mods) {}

    /*!
     * Returns a value from the Qt::Key enum corresponding to the key that triggered the event.
     */
    inline int key() const { return v; }
    /*!
     * Returns the keyboard modifiers pertaining to the keystroke that triggered the event.
     *
     * Note that not all modifiers or combinations of modifiers are available from the
     * curses backend.
     */
    inline Qt::KeyboardModifiers modifiers() const { return m; }
    /*!
     * Returns the native curses key code for the key that triggered the event.
     */
    inline int nativeScanCode() const { return k; }

private:
    int v, k;
    Qt::KeyboardModifiers m;
};

#endif
