/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtCore module of the Qxt library.
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
#include "qxttemporarydir.h"
#include "qxttemporarydir_p.h"

/*!
    \class QxtTemporaryDir
    \inmodule QxtCore
    \brief The QxtTemporaryDir class ...

    TODO

    Example usage:
    \code
    // ...
    \endcode

    \sa QTemporaryFile
*/

QxtTemporaryDirPrivate::QxtTemporaryDirPrivate() :
    autoRemove(true), init(false)
{
    templateName = QDir::temp().filePath(QLatin1String("qxt_temp_XXXXXX"));
}

static void qxt_removePathHelper(const QString& path)
{
    QDir dir(path);
    QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    foreach (const QFileInfo& entry, entries) {
        if (entry.isDir()) {
            qxt_removePathHelper(entry.path());
        } else {
            QFile::remove(entry.filePath());
        }
    }
    dir.rmdir(path);
}

void QxtTemporaryDirPrivate::remove()
{
    qxt_removePathHelper(dir.path());
}

QxtTemporaryDir::QxtTemporaryDir(const QString& templateName)
{
    QXT_INIT_PRIVATE(QxtTemporaryDir);
    if (!templateName.isNull())
        setTemplateName(templateName);
}

QxtTemporaryDir::~QxtTemporaryDir()
{
    if (qxt_d().init && qxt_d().autoRemove)
        qxt_d().remove();
}

QString QxtTemporaryDir::templateName() const
{
    return qxt_d().templateName;
}

void QxtTemporaryDir::setTemplateName(const QString& templateName)
{
    if (qxt_d().templateName != templateName)
    {
        if (qxt_d().init && qxt_d().autoRemove)
            qxt_d().remove();

        qxt_d().templateName = templateName;
        qxt_d().init = false;
    }
}

bool QxtTemporaryDir::autoRemove() const
{
    return qxt_d().autoRemove;
}

void QxtTemporaryDir::setAutoRemove(bool autoRemove)
{
    qxt_d().autoRemove = autoRemove;
}

QDir QxtTemporaryDir::dir() const
{
    if (!qxt_d().init)
    {
        QxtTemporaryDir* that = const_cast<QxtTemporaryDir*>(this);
        that->qxt_d().create();
        that->qxt_d().init = true;
    }
    return qxt_d().dir;
}

QString QxtTemporaryDir::path() const
{
    return dir().path();
}

QString QxtTemporaryDir::errorString() const
{
    return qxt_d().errorString;
}
