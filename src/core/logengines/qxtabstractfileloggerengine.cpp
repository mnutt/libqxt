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

#include "qxtabstractfileloggerengine.h"
// Abstract File Logger Engine
QxtAbstractFileLoggerEngine::QxtAbstractFileLoggerEngine( const QString &fileName ) : str_logFile(fileName) 
{
}
void QxtAbstractFileLoggerEngine::initLoggerEngine()
{	
    // Are we already logging to a file?  If so, close it and disable logging.
    this->killLoggerEngine();

	// If the file exists, check if we can write to it.  If we can, we append!
	// If the file doesn't exits, try to create it.
	// If we can't write to a file, disable this plugin.
    ptr_fileTarget = new QFile(str_logFile);
    if ( !ptr_fileTarget->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Unbuffered ) )
    {
        delete ptr_fileTarget;
		ptr_fileTarget= NULL;
        return;
    }
    else
    {
        if ( !ptr_fileTarget->isWritable() ) 
        {
            delete ptr_fileTarget;
			ptr_fileTarget = NULL;
            return;
        }
    }
    this->enableLogging();	
}

void QxtAbstractFileLoggerEngine::killLoggerEngine()
{
    if ( ptr_fileTarget != NULL )
    {
        if ( ptr_fileTarget->isOpen() ) ptr_fileTarget->close();
        delete ptr_fileTarget;
		ptr_fileTarget = NULL;
    }

}

void QxtAbstractFileLoggerEngine::setLogFile( const QString &fileName )
{
    str_logFile = fileName;
    this->initLoggerEngine();
}
QString QxtAbstractFileLoggerEngine::logFile() const
{
    return str_logFile;
}

bool QxtAbstractFileLoggerEngine::isInitialized() const
{
	return ( ptr_fileTarget != NULL );
}
