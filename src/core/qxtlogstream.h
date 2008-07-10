/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
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

#ifndef QXT__QXT_LOG_STREAM__H
#define QXT__QXT_LOG_STREAM__H
#include <QVariant>
#include <QList>
#include "qxtlogger.h"

// forward declaration
class QxtLogger;

class QxtLogStreamPrivate
{
public:
	QxtLogStreamPrivate( QxtLogger *owner, QxtLogger::LogLevel level, const QList<QVariant> &data);
	~QxtLogStreamPrivate();

	QxtLogger *owner;
	QxtLogger::LogLevel level;
	int refcount;	// Unfortunately, QExplicitlySharedDataPointer was introduced in Qt 4.4, and we have to work with Qt 4.2 ;_;
	QList<QVariant> data;
};

class QXT_CORE_EXPORT QxtLogStream
{
	friend class QxtLogger;
private:
	QxtLogStream( QxtLogger *owner, QxtLogger::LogLevel level, const QList<QVariant> &data);
	QxtLogStreamPrivate *d;
public:
	QxtLogStream( const QxtLogStream &other );
	~QxtLogStream();
	QxtLogStream& operator<< ( const QVariant &value );
};


#endif // QXT__QXT_LOG_STREAM__H

