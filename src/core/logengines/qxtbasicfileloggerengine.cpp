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

#include "qxtbasicfileloggerengine.h"
#include <QTime>
/**
	Constructor: initialize the file pointer to null.
*/
QxtBasicFileLoggerEngine::QxtBasicFileLoggerEngine()
{
	this->ptr_fileTarget	= NULL;
}


/**
	Destructor: close an open file, then delete.
*/
QxtBasicFileLoggerEngine::~QxtBasicFileLoggerEngine()
{
	this->killLoggerEngine();
}

void QxtBasicFileLoggerEngine::writeFormatted( QxtLogger::LogLevel level, const QList<QVariant> &messages )
{
		 if ( (level & QxtLogger::ErrorLevel)== QxtLogger::ErrorLevel )	writeToFile("Error", messages);
	else if ( (level & QxtLogger::WarningLevel) == QxtLogger::WarningLevel)	writeToFile("Warning", messages);
	else if ( (level & QxtLogger::CriticalLevel) == QxtLogger::CriticalLevel)	writeToFile("Critical", messages);
	else if ( (level & QxtLogger::FatalLevel)== QxtLogger::FatalLevel)	writeToFile("Fatal", messages);
	else if ( (level & QxtLogger::TraceLevel)== QxtLogger::TraceLevel)  writeToFile("Trace", messages);
	else if ( (level & QxtLogger::DebugLevel)== QxtLogger::DebugLevel ) writeToFile("Debug", messages);
	else if ( (level & QxtLogger::InfoLevel) == QxtLogger::InfoLevel )  writeToFile("Info", messages);
	else	writeToFile(QString(), messages);
}

void QxtBasicFileLoggerEngine::writeToFile(const QString &level, const QVariantList &messages)
{	
    if ( messages.isEmpty() ) return;
    QString header = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] [" + level + "] ";
    QString padding;
    ptr_fileTarget->write(header.toUtf8());
    for ( int i = 0; i < header.size(); i++ ) padding.append(" ");
    int count = 0;
    Q_FOREACH(QVariant out, messages )
    {
        if( !out.isNull() )
        {
            if ( count != 0 ) ptr_fileTarget->write(padding.toUtf8());
            ptr_fileTarget->write(out.toString().toUtf8()); 
            ptr_fileTarget->write("\n");
        }
        count++;
    }
}

