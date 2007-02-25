/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtApplication.h"
#include <QWidget>

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
