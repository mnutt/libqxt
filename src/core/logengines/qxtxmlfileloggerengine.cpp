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

#include "qxtxmlfileloggerengine.h"
#include <QTime>


/**
	Constructor: initialize the file pointer to null.
*/
QxtXmlFileLoggerEngine::QxtXmlFileLoggerEngine()
{
	ptr_fileTarget   = NULL;
	tab = "    ";
}


/**
	Destructor: close an open file, then delete.
*/
QxtXmlFileLoggerEngine::~QxtXmlFileLoggerEngine()
{
    this->killLoggerEngine();
}
// init
void QxtXmlFileLoggerEngine::initLoggerEngine()
{
    // Are we already logging to a file?  If so, close it and disable logging.
    this->killLoggerEngine();

    // If the file exists, check if we can write to it.  If we can, we append!
    // If the file doesn't exits, try to create it.
    // If we can't write to a file, disable this plugin.
    ptr_fileTarget = new QFile(str_logFile);
    if ( !ptr_fileTarget->open(QIODevice::ReadWrite | QIODevice::Unbuffered ) )
    {
        delete ptr_fileTarget;
        ptr_fileTarget = NULL;
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
   
    
    // Mkay, we have an open file.  We need to check that it's all valid.
    // at the end of this block of code, we either can't log, or the carat is ready for writing.
    /*
    <?xml version="1.0" encoding="UTF-8"?>
    <log>
        <entry type="Error" time="sometime">
            <message>What's going on?</message>
            <message?Hi there</message>
        </entry>
    </log>
    */
    if ( ptr_fileTarget->size() == 0 )
    {
        ptr_fileTarget->write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" );
        ptr_fileTarget->write("<log>\n");
        ptr_fileTarget->write("</log>");
    }
    else
    {
        QByteArray data = ptr_fileTarget->read(64);
        if ( !data.contains("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<log>") ) 
        {
            qxtLog->warning( QString(" is not a valid XML log file.").prepend( ptr_fileTarget->fileName() ) );
            ptr_fileTarget->close();
            delete ptr_fileTarget;
            ptr_fileTarget = NULL;
            return;
        }
        
    } 
    
    enableLogging();
}
void QxtXmlFileLoggerEngine::writeFormatted( QxtLogger::LogLevel level, const QVariantList &messages )
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

void QxtXmlFileLoggerEngine::writeToFile(const QString &level, const QVariantList &messages)
{	
        ptr_fileTarget->seek( ptr_fileTarget->size()-6 );
	ptr_fileTarget->write(tab.toUtf8() );
	ptr_fileTarget->write("<entry type=\"");
        ptr_fileTarget->write(level.toUtf8());
	ptr_fileTarget->write("\" time=\"");
        ptr_fileTarget->write(QTime::currentTime().toString("hh:mm:ss.zzzz").toUtf8());
	ptr_fileTarget->write("\">");
	ptr_fileTarget->write("\n");
	Q_FOREACH( QVariant m, messages )
	{
            ptr_fileTarget->write(tab.toUtf8()); ptr_fileTarget->write(tab.toUtf8());
		ptr_fileTarget->write("<message>");
                ptr_fileTarget->write( toXmlSafeString(m.toString()).toUtf8() );
		ptr_fileTarget->write("</message>\n");
	}
        
        ptr_fileTarget->write(tab.toUtf8()); ptr_fileTarget->write("</entry>"); ptr_fileTarget->write("\n");
        ptr_fileTarget->write("</log>");
}
QString QxtXmlFileLoggerEngine::toXmlSafeString( const QString &raw )
{
    /* Reserved characters:
    <  &lt;
    &  &amp;
    > &lt;
    ' &apos;
    " &quot;
    
    Convert ampersands first, then the rest.
    */
    return QByteArray(raw.toUtf8()).replace("&","&amp;").replace("<","&lt;").replace(">","&gt;").replace("'","&apos;").replace('"',"&quot;");
}
