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
#include <QtDebug>

/*!
    \class QxtTemporaryDir
    \inmodule QxtCore
    \brief The QxtTemporaryDir class ...

    TODO

    If the \a dirTemplate does not end with "XXXXXX" it will be automatically
    appended and used as the dynamic portion of the directory name.

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
    dirTemplate = QDir::temp().filePath(QLatin1String("qxt_temp"));
}

static bool qxt_removePathHelper(const QString& path)
{
    bool result = true;
    QDir dir(path);
    QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    foreach (const QFileInfo& entry, entries) {
        if (entry.isDir()) {
            qxt_removePathHelper(entry.path());
        } else {
            if (!QFile::remove(entry.filePath())) {
                qWarning() << "QxtTemporaryDir: unable to remove:" << entry.filePath();
                result = false;
            }
        }
    }
    if (!dir.rmdir(path)) {
        qWarning() << "QxtTemporaryDir: unable to remove:" << path;
        result = false;
    }
    return result;
}

/*!
    Constructs a new QxtTemporaryDir in QDir::tempPath(), using the dir
    name "qxt_temp". The temporary directory is created in the system's
    temporary directory.

    \sa setDirTemplate() QDir::tempPath()
*/
QxtTemporaryDir::QxtTemporaryDir()
{
    QXT_INIT_PRIVATE(QxtTemporaryDir);
}

/*!
    Constructs a new QxtTemporaryDir with \a dirTemplate.

    If \a dirTemplate is a relative path, the path will be relative to the
    current working directory. You can use QDir::tempPath() to construct
    \a dirTemplate if you want use the system's temporary directory.

    \sa dirTemplate() QDir::tempPath()
*/
QxtTemporaryDir::QxtTemporaryDir(const QString& dirTemplate)
{
    QXT_INIT_PRIVATE(QxtTemporaryDir);
    setDirTemplate(dirTemplate);
}

/*!
    Destructs the temporary dir. The temporary dir is automatically
    removed if in auto remove mode.

    \sa autoRemove()
*/
QxtTemporaryDir::~QxtTemporaryDir()
{
    if (qxt_d().init && qxt_d().autoRemove)
        remove();
}

/*!
    Returns the template name. The default template name will be called
    "qxt_temp_XXXXXX" and be placed in QDir::tempPath().

    \sa setDirTemplate()
*/
QString QxtTemporaryDir::dirTemplate() const
{
    return qxt_d().dirTemplate;
}

/*!
    Sets the static portion of the dir name to \a dirTemplate.
    If the template name ends in XXXXXX that will automatically be replaced
    with the unique part of the dir name, otherwise a dir name will be
    determined automatically based on the static portion specified.

    If name contains a relative file path, the path will be relative to the
    current working directory. You can use QDir::tempPath() to construct name
    if you want use the system's temporary directory.

    \sa dirTemplate()
*/
void QxtTemporaryDir::setDirTemplate(const QString& dirTemplate)
{
    if (qxt_d().dirTemplate != dirTemplate)
    {
        if (qxt_d().init && qxt_d().autoRemove)
            remove();

        qxt_d().dirTemplate = dirTemplate;
        qxt_d().init = false;
    }
}

/*!
    Returns \c true if the QxtTemporaryDir is in auto remove mode.
    Auto-remove mode will automatically remove the directory from disk upon destruction.
    This makes it very easy to create QxtTemporaryDir object on the stack, fill it with data,
    read from it, and finally on function return it will automatically clean up after itself.

    Auto-remove is on by default.

    \sa setAutoRemove() remove()
*/
bool QxtTemporaryDir::autoRemove() const
{
    return qxt_d().autoRemove;
}

/*!
    Sets the QxtTemporaryDir into auto-remove mode if autoRemove is \c true.

    Auto-remove is on by default.

    \sa autoRemove() remove()
*/
void QxtTemporaryDir::setAutoRemove(bool autoRemove)
{
    qxt_d().autoRemove = autoRemove;
}

bool QxtTemporaryDir::remove()
{
    if (!qxt_d().init)
        return false;
    return qxt_removePathHelper(path());
}

QDir QxtTemporaryDir::dir() const
{
    if (!qxt_d().init)
    {
        QxtTemporaryDir* that = const_cast<QxtTemporaryDir*>(this);
        QString path = that->qxt_d().create();
        if (!path.isNull()) {
            that->qxt_d().dir.setPath(path);
            that->qxt_d().init = true;
        } else {
            that->qxt_d().error = qt_error_string();
        }
    }
    return qxt_d().dir;
}

QString QxtTemporaryDir::path() const
{
    return dir().path();
}

QString QxtTemporaryDir::errorString() const
{
    return qxt_d().error;
}
