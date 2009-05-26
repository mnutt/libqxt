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
#include "qxtglobalshortcut_p.h"
#include <QX11Info>
#include <X11/Xlib.h>

bool QxtGlobalShortcutPrivate::eventFilter(void* message)
{
    XEvent* event = static_cast<XEvent*>(message);
    if (event->type == KeyPress)
    {
        XKeyEvent* key = (XKeyEvent*) event;
        activateShortcut(key->keycode, 
            // Mod1Mask == Alt, Mod4Mask == Meta
            key->state & (ShiftMask | ControlMask | Mod1Mask | Mod4Mask));
    }
    return false;
}

quint32 QxtGlobalShortcutPrivate::nativeModifiers(Qt::KeyboardModifiers modifiers)
{
    // ShiftMask, LockMask, ControlMask, Mod1Mask, Mod2Mask, Mod3Mask, Mod4Mask, and Mod5Mask
    quint32 native = 0;
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

quint32 QxtGlobalShortcutPrivate::nativeKeycode(Qt::Key key)
{
    Display* display = QX11Info::display();
    return XKeysymToKeycode(display, XStringToKeysym(QKeySequence(key).toString().toLatin1().data()));
}

bool QxtGlobalShortcutPrivate::registerShortcut(quint32 nativeKey, quint32 nativeMods)
{
    Display* display = QX11Info::display();
    Window window = QX11Info::appRootWindow();
    Bool owner = True;
    int pointer = GrabModeAsync;
    int keyboard = GrabModeAsync;
    // no way to check for success
    XGrabKey(display, nativeKey, nativeMods, window, owner, pointer, keyboard);
    // allow numlock
    XGrabKey(display, nativeKey, nativeMods | Mod2Mask, window, owner, pointer, keyboard);
    return true;
}

bool QxtGlobalShortcutPrivate::unregisterShortcut(quint32 nativeKey, quint32 nativeMods)
{
    Display* display = QX11Info::display();
    Window window = QX11Info::appRootWindow();
    // no way to check for success
    XUngrabKey(display, nativeKey, nativeMods, window);
    XUngrabKey(display, nativeKey, nativeMods | Mod2Mask, window);
    return true;
}
