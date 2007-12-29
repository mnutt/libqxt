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
#ifndef QXTGLOBALSHORTCUT_H
#define QXTGLOBALSHORTCUT_H

#include "qxtglobal.h"
#include "qxtpimpl.h"
#include <QObject>
#include <QKeySequence>
class QxtGlobalShortcutPrivate;

class QXT_GUI_EXPORT QxtGlobalShortcut : public QObject
{
    Q_OBJECT
    QXT_DECLARE_PRIVATE(QxtGlobalShortcut);
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(QKeySequence shortcut READ shortcut WRITE setShortcut)

public:
    explicit QxtGlobalShortcut(QObject* parent = 0);
    explicit QxtGlobalShortcut(const QKeySequence& shortcut, QObject* parent = 0);
    virtual ~QxtGlobalShortcut();

    QKeySequence shortcut() const;
    bool setShortcut(const QKeySequence& shortcut);

    bool isEnabled() const;

public slots:
    void setEnabled(bool enabled = true);
    void setDisabled(bool disabled = true);

signals:
    void activated();
};

#endif // QXTGLOBALSHORTCUT_H
