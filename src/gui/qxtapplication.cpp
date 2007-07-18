/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/
#include "qxtapplication.h"
#include <QWidget>

/*!
    \class QxtApplication QxtApplication
    \ingroup gui
    \brief An extended QApplication with support for hotkeys aka "global shortcuts".

    QxtApplication introduces hotkeys which trigger even if the application is not
    active. This makes it easy to implement applications that react to certain
    shortcuts still if some other application is active or if the application is
    for example minimized to the system tray.

    \note Currently supported platforms are \b X11 and \b Windows.
 */

/*!
    \fn QxtApplication::instance()

    Returns a pointer to the instance of the application object.

    A convenience macro \b qxtApp is also available.
 */

QxtApplication::QxtApplication(int& argc, char** argv)
	: QApplication(argc, argv)
{
}

QxtApplication::QxtApplication(int& argc, char** argv, bool GUIenabled)
	: QApplication(argc, argv, GUIenabled)
{
}

QxtApplication::QxtApplication(int& argc, char** argv, Type type)
	: QApplication(argc, argv, type)
{
}

QxtApplication::~QxtApplication()
{
}

/*!
    Adds a hotkey using \a modifiers and \a key. The \a member
    of \a receiver is invoked upon hotkey trigger.

    \return \b true if hotkey registration succeed, \b false otherwise.

    Example usage:
    \code
    QxtLabel* label = new QxtLabel("Hello world!");
    qxtApp->addHotKey(Qt::ShiftModifier | Qt::ControlModifier, Qt::Key_S, label, "show");
    \endcode
*/
bool QxtApplication::addHotKey(Qt::KeyboardModifiers modifiers, Qt::Key key, QWidget* receiver, const char* member)
{
	Q_ASSERT(receiver);
	Q_ASSERT(member);
	uint mods = nativeModifiers(modifiers);
	uint keycode = nativeKeycode(key);
	if (keycode)
	{
		hotkeys.insert(qMakePair(mods, keycode), qMakePair(receiver, member));
		return registerHotKey(mods, keycode, receiver);
	}
	return false;
}

/*!
    Removes the hotkey using \a modifiers and \a key mapped to
    \a member of \a receiver.

    \return \b true if hotkey unregistration succeed, \b false otherwise.
*/
bool QxtApplication::removeHotKey(Qt::KeyboardModifiers modifiers, Qt::Key key, QWidget* receiver, const char* member)
{
	Q_ASSERT(receiver);
	Q_UNUSED(member);
	uint mods = nativeModifiers(modifiers);
	uint keycode = nativeKeycode(key);
	if (keycode)
	{
		hotkeys.remove(qMakePair(mods, keycode));
		return unregisterHotKey(mods, keycode, receiver);
	}
	return false;
}

void QxtApplication::activateHotKey(uint modifiers, uint keycode) const
{
	Receivers receivers = hotkeys.values(qMakePair(modifiers, keycode));
	foreach (Receiver receiver, receivers)
	{
		// QMetaObject::invokeMethod() has appropriate null checks
		QMetaObject::invokeMethod(receiver.first, receiver.second);
	}
}
