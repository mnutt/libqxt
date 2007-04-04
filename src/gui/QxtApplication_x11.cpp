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


#include "QxtApplication.h"
#include <QKeySequence>
#include <QX11Info>
#include <X11/Xlib.h>

QxtApplication::QxtApplication(Display* display, Qt::HANDLE visual, Qt::HANDLE colormap)
	: QApplication(display, visual, colormap)
{
}

QxtApplication::QxtApplication(Display* display, int& argc, char** argv, Qt::HANDLE visual, Qt::HANDLE colormap)
	: QApplication(display, argc, argv, visual, colormap)
{
}

bool QxtApplication::x11EventFilter(XEvent* event)
{
	if (event->type == KeyPress)
	{
		XKeyEvent* key = (XKeyEvent*) event;
		activateHotKey(key->state, key->keycode);
	}
	return QApplication::x11EventFilter(event);
}

uint QxtApplication::nativeModifiers(Qt::KeyboardModifiers modifiers) const
{
	// ShiftMask, LockMask, ControlMask, Mod1Mask, Mod2Mask, Mod3Mask, Mod4Mask, and Mod5Mask
	uint native = 0;
	if (modifiers & Qt::ShiftModifier)
		native |= ShiftMask;
	if (modifiers & Qt::ControlModifier)
		native |= ControlMask;
	if (modifiers & Qt::AltModifier)
		native |= Mod1Mask;
	// TODO: resolve these?
	//if (modifiers & Qt::MetaModifier)
	//if (modifiers & Qt::KeypadModifier)
	//if (modifiers & Qt::GroupSwitchModifier)
	return native;
}

uint QxtApplication::nativeKeycode(Qt::Key key) const
{
	Display* display = QX11Info::display();
	return XKeysymToKeycode(display, XStringToKeysym(QKeySequence(key).toString().toLatin1().data()));
}

bool QxtApplication::registerHotKey(uint modifiers, uint keycode, QWidget* receiver)
{
	Q_UNUSED(receiver);
	Display* display = QX11Info::display();
	Window window = QX11Info::appRootWindow();
	Bool owner = True;
	int pointer = GrabModeAsync;
	int keyboard = GrabModeAsync;
	return XGrabKey(display, keycode, modifiers, window, owner, pointer, keyboard);
}

bool QxtApplication::unregisterHotKey(uint modifiers, uint keycode, QWidget* receiver)
{
	Q_UNUSED(receiver);
	Display* display = QX11Info::display();
	Window window = QX11Info::appRootWindow();
	return XUngrabKey(display, keycode, modifiers, window);
}
