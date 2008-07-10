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

#ifndef QXT__QBASIC__STD__LOGGER_ENGINE_H
#define QXT__QBASIC__STD__LOGGER_ENGINE_H
#include "qxtloggerengine.h"
#include <QTextStream>

/*******************************************************************************
	QBasicSTDLoggerEngine
	The basic logger engine included with QxtLogger.
*******************************************************************************/
class QXT_CORE_EXPORT QxtBasicSTDLoggerEngine : public QxtLoggerEngine
{
public:
	 QxtBasicSTDLoggerEngine	();
	~QxtBasicSTDLoggerEngine	();

	void	initLoggerEngine      ();
	void	killLoggerEngine      ();
	void	writeFormatted	( QxtLogger::LogLevel level, const QList<QVariant> &messages );
	void	setLogLevelEnabled( QxtLogger::LogLevels level, bool enable = true );

	bool	isInitialized () const;

protected:
	void WriteToSTDERR	( const QString& str_level, const QList<QVariant> &msgs );
	void WriteToSTDOUT	( const QString& str_level, const QList<QVariant> &msgs );
	QTextStream *errstream, *outstream;
	QxtLogger::LogLevels	bm_reqLevels;


};
#endif //QXT__QBASIC__STD__LOGGER_ENGINE_H

