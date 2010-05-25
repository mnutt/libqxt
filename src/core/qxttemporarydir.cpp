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

static QString defaultDirTemplate()
{
    return QDir::temp().filePath(QLatin1String("qxt"));
}

static bool qxt_removePathHelper(const QString& path)
{
    bool result = true;
    QDir dir(path);
    if (!dir.exists())
        return false;
    QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    foreach (const QFileInfo& entry, entries) {
        if (entry.isDir()) {
            qxt_removePathHelper(entry.filePath());
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

QxtTemporaryDirPrivate::QxtTemporaryDirPrivate() :
    autoRemove(true), init(false)
{
    dirTemplate = defaultDirTemplate();
}

void QxtTemporaryDirPrivate::validate()
{
    if (dirTemplate.isEmpty())
        dirTemplate = defaultDirTemplate();

    QFileInfo info(dirTemplate);
    if (info.isDir())
        dirTemplate = QDir(dirTemplate).filePath(QLatin1String("qxt"));
}

/*!
    \class QxtTemporaryDir
    \inmodule QxtCore
    \brief The QxtTemporaryDir class manages temporary directories.

    QxtTemporaryDir is used to create unique temporary directories.
    The directory itself is created when calling dir() or path().
    The name of the temporary directory is guaranteed to be unique
    (i.e., you are guaranteed to not overwrite an existing directory),
    and the directory will subsequently be removed upon destruction of
    the QxtTemporaryDir object. This is an important technique that
    avoids data corruption for applications that store data in temporary
    directories. The directory name is based on a template, which can be
    passed to QxtTemporaryDir's constructor.

    A temporary directory will have some static part of the name and some
    part that is calculated to be unique. The default directory template
    "qxt" will be placed into the temporary path as returned by
    QDir::tempPath(). If you specify your own directory template
    a relative file path will not be placed in the temporary directory
    by default, but be relative to the current working directory.

    \sa QDir::tempPath(), QTemporaryFile
*/

/*!
    Constructs a new QxtTemporaryDir in QDir::tempPath(), using the
    default dir template ("qxt").

    \sa setDirTemplate(), QDir::tempPath()
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

    \sa dirTemplate(), QDir::tempPath()
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
    Returns the directory template. The default directory template is called
    "qxt" and be placed in QDir::tempPath().

    \sa setDirTemplate()
*/
QString QxtTemporaryDir::dirTemplate() const
{
    return qxt_d().dirTemplate;
}

/*!
    Sets the static portion of the dir name to \a dirTemplate.

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

    \sa setAutoRemove(), remove()
*/
bool QxtTemporaryDir::autoRemove() const
{
    return qxt_d().autoRemove;
}

/*!
    Sets the QxtTemporaryDir into auto-remove mode if \a autoRemove is \c true.

    Auto-remove is on by default.

    \sa autoRemove(), remove()
*/
void QxtTemporaryDir::setAutoRemove(bool autoRemove)
{
    qxt_d().autoRemove = autoRemove;
}

/*!
    Removes the temporary directory from disk.
    Returns \c true if removal succeed, \c false otherwise.
*/
bool QxtTemporaryDir::remove()
{
    if (!qxt_d().init)
        return false;
    return qxt_removePathHelper(dir().absolutePath());
}

/*!
    Returns a QDir object pointing to the temporary directory.

    \sa path()
*/
QDir QxtTemporaryDir::dir() const
{
    if (!qxt_d().init)
    {
        QxtTemporaryDirPrivate& that = const_cast<QxtTemporaryDir*>(this)->qxt_d();
        that.validate();
        QString path = that.create();
        if (!path.isNull()) {
            that.dir.setPath(path);
            that.init = true;
        } else {
            that.error = qt_error_string();
        }
    }
    return qxt_d().dir;
}

/*!
    Returns path to the temporary directory.

    \sa dir()
*/
QString QxtTemporaryDir::path() const
{
    return dir().path();
}

/*!
    Returns a human-readable description of the last device error that occurred.
*/
QString QxtTemporaryDir::errorString() const
{
    return qxt_d().error;
}
