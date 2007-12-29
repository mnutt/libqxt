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
#include "qxtglobalshortcut.h"
#include "qxtglobalshortcut_p.h"
#include <QKeyEvent>

QxtGlobalShortcutPrivate::QxtGlobalShortcutPrivate() : key(Qt::Key(0)), mods(Qt::NoModifier)
#ifdef Q_WS_WIN
    , widget(0)
#endif // Q_WS_WIN
{
}

bool QxtGlobalShortcutPrivate::setShortcut(Qt::Key keycode, Qt::KeyboardModifiers modifiers)
{
    key = keycode;
    mods = modifiers;
    return registerShortcut(nativeKeycode(key), nativeModifiers(mods));
}

bool QxtGlobalShortcutPrivate::unsetShortcut()
{
    bool res = unregisterShortcut(nativeKeycode(key), nativeModifiers(mods));
    key = Qt::Key(0);
    mods = Qt::KeyboardModifiers(0);
    return res;
}

void QxtGlobalShortcutPrivate::activateShortcut(quint32 nativeKey, quint32 nativeMods)
{
    if (nativeKeycode(key) == nativeKey && nativeModifiers(mods) == nativeMods)
        emit qxt_p().activated();
}

/*!
    \class QxtGlobalShortcut QxtGlobalShortcut
    \ingroup QxtGui
    \brief A global shortcut aka "hotkey".

    A global shortcut triggers even if the application is not active. This
    makes it easy to implement applications that react to certain shortcuts
    still if some other application is active or if the application is for
    example minimized to the system tray.
 */

QxtGlobalShortcut::QxtGlobalShortcut(QObject* parent)
    : QObject(parent)
{
    Q_ASSERT(qxtApp);
    QXT_INIT_PRIVATE(QxtGlobalShortcut);
    qxtApp->installNativeEventFilter(&qxt_d());
}

QxtGlobalShortcut::QxtGlobalShortcut(Qt::Key key, Qt::KeyboardModifiers modifiers, QObject* parent)
    : QObject(parent)
{
    Q_ASSERT(qxtApp);
    QXT_INIT_PRIVATE(QxtGlobalShortcut);
    qxtApp->installNativeEventFilter(&qxt_d());
    setShortcut(key, modifiers);
}

QxtGlobalShortcut::~QxtGlobalShortcut()
{
    if (qxt_d().key != 0)
        qxt_d().unsetShortcut();
}

Qt::Key QxtGlobalShortcut::key() const
{
    return qxt_d().key;
}

Qt::KeyboardModifiers QxtGlobalShortcut::modifiers() const
{
    return qxt_d().mods;
}

bool QxtGlobalShortcut::setShortcut(Qt::Key key, Qt::KeyboardModifiers modifiers)
{
    if (qxt_d().key != 0)
        qxt_d().unsetShortcut();
    return qxt_d().setShortcut(key, modifiers);
}
