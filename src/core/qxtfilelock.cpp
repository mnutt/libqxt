/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
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
#include "qxtfilelock.h"
#include "qxtfilelock_p.h"
/**
\class QxtFileLock QxtFileLock

\ingroup core

\brief Lock regions of, or a whole file

\warning not part of 0.2.4
*/
QxtFileLockPrivate::QxtFileLockPrivate()  : offset(0), length(0), mode(QxtFileLock::WriteLockWait), isLocked(false)
{
    
}

 QxtFileLock::QxtFileLock(QFile *file,const off_t offset,const off_t length,const QxtFileLock::Mode mode) : QObject(file)
{
    QXT_INIT_PRIVATE(QxtFileLock);
    connect(file,SIGNAL(aboutToClose()),this,SLOT(unlock()));
    qxt_d().offset = offset;
    qxt_d().length = length;
    qxt_d().mode = mode;
}

QxtFileLock::~QxtFileLock()
{
    unlock();
}

off_t QxtFileLock::offset() const
{
    return qxt_d().offset;
}

bool QxtFileLock::isActive() const
{
    return qxt_d().isLocked;
}

off_t QxtFileLock::length() const
{
    return qxt_d().length;
}

QFile * QxtFileLock::file() const
{
    return qobject_cast<QFile *>(parent());
}

QxtFileLock::Mode QxtFileLock::mode() const
{
    return qxt_d().mode;
}
