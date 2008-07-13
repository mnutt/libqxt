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

/*!
    \class QxtAbstractFileLoggerEngine QxtAbstractFileLoggerEngine
    \brief The base class of file logger engines.
    \ingroup QxtCore

    \sa QxtLogger
 */

class QxtAbstractFileLoggerEnginePrivate : public QxtPrivate<QxtAbstractFileLoggerEngine>
{
    QXT_DECLARE_PUBLIC(QxtAbstractFileLoggerEngine);

public:
    QString logFile;
};

/*!
    Constructs a QxtAbstractFileLoggerEngine with file name.
 */
QxtAbstractFileLoggerEngine::QxtAbstractFileLoggerEngine( const QString &fileName )
    : QxtAbstractIOLoggerEngine(0)
{
    QXT_INIT_PRIVATE(QxtAbstractFileLoggerEngine);
    setLogFileName(fileName);
}

/*!
    Destructs the file logger engine.
 */
QxtAbstractFileLoggerEngine::~QxtAbstractFileLoggerEngine()
{
    killLoggerEngine();
}

/*!
    \reimp
 */
void QxtAbstractFileLoggerEngine::initLoggerEngine()
{
    // Are we already logging to a file?  If so, close it and disable logging.
    killLoggerEngine();

    // If the file exists, check if we can write to it.  If we can, we append!
    // If the file doesn't exits, try to create it.
    // If we can't write to a file, disable this plugin.
    setDevice(new QFile(qxt_d().logFile));
    if ( !device()->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Unbuffered )
          || !device()->isWritable() )
    {
        killLoggerEngine();
    }

    enableLogging();
}

/*!
    \reimp
 */
void QxtAbstractFileLoggerEngine::killLoggerEngine()
{
    if ( device() != 0 )
    {
        if ( device()->isOpen() ) device()->close();
        delete device();
        setDevice( 0 );
    }
}

/*!
    \reimp
 */
bool QxtAbstractFileLoggerEngine::isInitialized() const
{
    return ( device() != 0 );
}

/*!
    \reimp
 */
void QxtAbstractFileLoggerEngine::writeFormatted( QxtLogger::LogLevel level, const QList<QVariant> &messages )
{
    if ( (level & QxtLogger::ErrorLevel)== QxtLogger::ErrorLevel )  writeToFile("Error", messages);
    else if ( (level & QxtLogger::WarningLevel) == QxtLogger::WarningLevel) writeToFile("Warning", messages);
    else if ( (level & QxtLogger::CriticalLevel) == QxtLogger::CriticalLevel)   writeToFile("Critical", messages);
    else if ( (level & QxtLogger::FatalLevel)== QxtLogger::FatalLevel)  writeToFile("Fatal", messages);
    else if ( (level & QxtLogger::TraceLevel)== QxtLogger::TraceLevel)  writeToFile("Trace", messages);
    else if ( (level & QxtLogger::DebugLevel)== QxtLogger::DebugLevel ) writeToFile("Debug", messages);
    else if ( (level & QxtLogger::InfoLevel) == QxtLogger::InfoLevel )  writeToFile("Info", messages);
    else    writeToFile(QString(), messages);
}

/*!
    Sets the log file name.
 */
void QxtAbstractFileLoggerEngine::setLogFileName( const QString &fileName )
{
    qxt_d().logFile = fileName;
    initLoggerEngine();
}

/*!
    Returns the log file name.
 */
QString QxtAbstractFileLoggerEngine::logFileName() const
{
    return qxt_d().logFile;
}

/*!
    \fn virtual void QxtAbstractFileLoggerEngine::writeToFile( const QString &level, const QVariantList &messages ) = 0

    Writes to file.

    This function is called by QxtAbstractFileLoggerEngine. Reimplement this function when creating a subclass of QxtAbstractFileLoggerEngine.
 */
