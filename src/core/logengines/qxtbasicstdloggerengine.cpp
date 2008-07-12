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

#include "qxtbasicstdloggerengine.h"
#include <QTextStream>
#include <QTime>

#define QXT_REQUIRED_LEVELS (QxtLogger::WarningLevel | QxtLogger::ErrorLevel | QxtLogger::CriticalLevel | QxtLogger::FatalLevel)

class QxtBasicSTDLoggerEnginePrivate : public QxtPrivate<QxtBasicSTDLoggerEngine>
{
    QXT_DECLARE_PUBLIC(QxtBasicSTDLoggerEngine);

public:
    QxtBasicSTDLoggerEnginePrivate();

    QTextStream *errstream, *outstream;
    QxtLogger::LogLevels bm_reqLevels;
};

QxtBasicSTDLoggerEnginePrivate::QxtBasicSTDLoggerEnginePrivate()
    : bm_reqLevels(0)
{
    errstream = new QTextStream(stderr);
    outstream = new QTextStream(stdout);
}

/*******************************************************************************
    CONSTRUCTOR
    sets up logging to STDERR with default flags. (the top 3 log levels )
*******************************************************************************/
QxtBasicSTDLoggerEngine::QxtBasicSTDLoggerEngine()
{
    QXT_INIT_PRIVATE(QxtBasicSTDLoggerEngine);
#ifndef QT_NO_DEBUG
    setLogLevelEnabled(QXT_REQUIRED_LEVELS);
#else
    setLogLevelEnabled(QXT_REQUIRED_LEVELS | QxtLogger::DebugLevel);
#endif
    enableLogging();
}

/*******************************************************************************
    DESTRUCTOR
    Properly close the File pointer to STDERR
*******************************************************************************/
QxtBasicSTDLoggerEngine::~QxtBasicSTDLoggerEngine()
{
    if (qxt_d().errstream)
    {
        qxt_d().errstream->flush();
        delete qxt_d().errstream;
        qxt_d().errstream = 0;
    }
    if (qxt_d().outstream)
    {
        qxt_d().outstream->flush();
        delete qxt_d().outstream;
        qxt_d().errstream = 0;
    }
}

/*******************************************************************************
    initLoggerEngine()
    Doesn't do anthing for the default logger.
*******************************************************************************/
void QxtBasicSTDLoggerEngine::initLoggerEngine()
{
    return; // Should work out of the box!
}

/*******************************************************************************
    killLoggerEngine()
    Doesn't do anything for the default logger.
*******************************************************************************/
void QxtBasicSTDLoggerEngine::killLoggerEngine()
{
    return; // I do nothing.
}

bool QxtBasicSTDLoggerEngine::isInitialized() const
{
    return qxt_d().errstream && qxt_d().outstream;
}

QTextStream* QxtBasicSTDLoggerEngine::stdErrStream() const
{
    return qxt_d().errstream;
}

QTextStream* QxtBasicSTDLoggerEngine::stdOutStream() const
{
    return qxt_d().outstream;
}

/*******************************************************************************
    isLoggable
    Checks if the given log level(s) are enabled for logging and returns true.
    The STD engine requires that the Warning+ levels are always logged if
    this engine is logging, so this will return true.
*******************************************************************************/
void QxtBasicSTDLoggerEngine::setLogLevelEnabled( QxtLogger::LogLevels level, bool enable )
{
    QxtLoggerEngine::setLogLevelEnabled(level | QXT_REQUIRED_LEVELS, enable);
    if ( !enable) QxtLoggerEngine::setLogLevelEnabled( QXT_REQUIRED_LEVELS );
}

/*******************************************************************************
    writeFormatted
    Writes Messages to STDERR and STDOUT
*******************************************************************************/
void QxtBasicSTDLoggerEngine::writeFormatted( QxtLogger::LogLevel level, const QList<QVariant> &msgs )
{
    if ( level & QxtLogger::ErrorLevel )
    {
        writeToStdErr("Error", msgs);
    }
    else if ( level & QxtLogger::WarningLevel)
    {
        writeToStdOut("Warning", msgs);
    }
    else if ( level & QxtLogger::CriticalLevel )
    {
        writeToStdErr("Critical", msgs);
    }
    else if ( level & QxtLogger::FatalLevel )
    {
        writeToStdErr("!!FATAL!!", msgs);
    }
    else if ( level & QxtLogger::TraceLevel )
    {
        writeToStdOut("Trace", msgs);
    }
    else if ( level & QxtLogger::DebugLevel )
    {
        writeToStdErr("DEBUG", msgs);
    }
    else if ( level & QxtLogger::InfoLevel )
    {
        writeToStdOut("INFO", msgs);
    }
    else
    {
        writeToStdOut("", msgs);
    }
}

/*******************************************************************************
    writeToStdErr
    A helper function that actually writes to stderr.
*******************************************************************************/
void QxtBasicSTDLoggerEngine::writeToStdErr( const QString &level, const QList<QVariant> &msgs )
{
    if ( msgs.isEmpty() ) return;
    QString header = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] [" + level + "] ";
    QString padding;
    QTextStream* errstream = stdErrStream();
    Q_ASSERT(errstream);
    *errstream << header;
    for ( int i = 0; i < header.size(); i++ ) padding.append(" ");
    int count = 0;
    Q_FOREACH(QVariant out, msgs )
    {
        if( !out.isNull() )
        {
            if ( count != 0 ) *errstream << padding;
            *errstream << out.toString() << '\n';
        }
        count++;
    }
    *errstream << endl;
}

/*******************************************************************************
    writeToStdOut
    A helper function that actually writes to stdout.
*******************************************************************************/
void QxtBasicSTDLoggerEngine::writeToStdOut( const QString& level, const QList<QVariant> &msgs )
{
    /* Message format...
        [time] [error level] First message.....
                    second message
                    third message
    */
    if ( msgs.isEmpty() ) return;
    QString header = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] [" + level + "] ";
    QString padding;
    QTextStream* outstream = stdOutStream();
    Q_ASSERT(outstream);
    *outstream << header;
    for ( int i = 0; i < header.size(); i++ ) padding.append(" ");
    int count = 0;
    Q_FOREACH(QVariant out, msgs )
    {
        if( !out.isNull() )
        {
            if ( count != 0 ) *outstream << padding;
            *outstream << out.toString() << '\n';
        }
        count++;
    }
    *outstream << endl;
}
