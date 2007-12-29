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

QxtGlobalShortcutPrivate::QxtGlobalShortcutPrivate() : enabled(true), key(Qt::Key(0)), mods(Qt::NoModifier)
#ifdef Q_WS_WIN
    , widget(0)
#endif // Q_WS_WIN
{
}

bool QxtGlobalShortcutPrivate::setShortcut(const QKeySequence& shortcut)
{
    key = shortcut.isEmpty() ? Qt::Key(0) : Qt::Key(shortcut[0] & 0x01FFFFFF);
    mods = shortcut.isEmpty() ? Qt::KeyboardModifiers(0) : Qt::KeyboardModifiers(shortcut[0] & 0xFE000000);
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
    if (enabled && nativeKeycode(key) == nativeKey && nativeModifiers(mods) == nativeMods)
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

QxtGlobalShortcut::QxtGlobalShortcut(const QKeySequence& shortcut, QObject* parent)
    : QObject(parent)
{
    Q_ASSERT(qxtApp);
    QXT_INIT_PRIVATE(QxtGlobalShortcut);
    qxtApp->installNativeEventFilter(&qxt_d());
    setShortcut(shortcut);
}

QxtGlobalShortcut::~QxtGlobalShortcut()
{
    if (qxt_d().key != 0)
        qxt_d().unsetShortcut();
}

/*!
    \property QxtGlobalShortcut::shortcut
    \brief This property holds the shortcut key sequence
 */
QKeySequence QxtGlobalShortcut::shortcut() const
{
    return QKeySequence(qxt_d().key, qxt_d().mods);
}

bool QxtGlobalShortcut::setShortcut(const QKeySequence& shortcut)
{
    if (qxt_d().key != 0)
        qxt_d().unsetShortcut();
    return qxt_d().setShortcut(shortcut);
}

/*!
    \property QxtGlobalShortcut::enabled
    \brief This property holds whether the shortcut is enabled

    A disabled shortcut does not get activated.

    The default value is \b true.

    \sa setDisabled()
 */
bool QxtGlobalShortcut::isEnabled() const
{
    return qxt_d().enabled;
}

void QxtGlobalShortcut::setEnabled(bool enabled)
{
    qxt_d().enabled = enabled;
}

/*!
    Sets the shortcut \a disabled.

    \sa enabled
 */
void QxtGlobalShortcut::setDisabled(bool disabled)
{
    qxt_d().enabled = !disabled;
}
