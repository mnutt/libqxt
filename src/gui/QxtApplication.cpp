/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtApplication.h"
#include <QWidget>

/*!
    \class QxtApplication QxtApplication
    \ingroup gui
    \brief An application with support for hotkeys aka "global shortcuts".

    QxtApplication introduces hotkeys which trigger
    even if the application is not active.

    \note Currently supported platforms are \b X11 and \b Windows.
 */

/*!
    \fn QxtApplication::instance()

    Returns a pointer to the instance of the application.
 */

/*!
    Constructs a new QxtApplication. All other variations
    of QApplication constructors are supported too.
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
