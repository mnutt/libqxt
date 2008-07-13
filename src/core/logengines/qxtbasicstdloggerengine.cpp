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

/*!
    \class QxtBasicSTDLoggerEngine QxtBasicSTDLoggerEngine
    \brief A basic STD logger engine.
    \ingroup QxtCore

    \sa QxtLogger
 */

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

/*!
    Constructor.
 */
QxtBasicSTDLoggerEngine::QxtBasicSTDLoggerEngine()
{
    QXT_INIT_PRIVATE(QxtBasicSTDLoggerEngine);
#ifndef QT_NO_DEBUG
    setLogLevelsEnabled(QXT_REQUIRED_LEVELS);
#else
    setLogLevelsEnabled(QXT_REQUIRED_LEVELS | QxtLogger::DebugLevel);
#endif
    enableLogging();
}

/*!
    Destructor.
 */
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

/*!
    \reimp
 */
void QxtBasicSTDLoggerEngine::initLoggerEngine()
{
    return; // Should work out of the box!
}

/*!
    \reimp
 */
void QxtBasicSTDLoggerEngine::killLoggerEngine()
{
    return; // I do nothing.
}

/*!
    \reimp
 */
bool QxtBasicSTDLoggerEngine::isInitialized() const
{
    return qxt_d().errstream && qxt_d().outstream;
}

/*!
    Returns the stderr stream.
 */
QTextStream* QxtBasicSTDLoggerEngine::stdErrStream() const
{
    return qxt_d().errstream;
}

/*!
    Returns the stdout stream.
 */
QTextStream* QxtBasicSTDLoggerEngine::stdOutStream() const
{
    return qxt_d().outstream;
}

/*!
    \reimp
 */
void QxtBasicSTDLoggerEngine::setLogLevelEnabled( QxtLogger::LogLevels level, bool enable )
{
    QxtLoggerEngine::setLogLevelsEnabled(level | QXT_REQUIRED_LEVELS, enable);
    if ( !enable) QxtLoggerEngine::setLogLevelsEnabled( QXT_REQUIRED_LEVELS );
}

/*!
    \reimp
 */
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

/*!
    A helper function that actually writes to stderr.

    This function is called by QxtBasicSTDLoggerEngine. Reimplement this function when creating a subclass of QxtBasicSTDLoggerEngine.
 */
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

/*!
    A helper function that actually writes to stdout.

    This function is called by QxtBasicSTDLoggerEngine. Reimplement this function when creating a subclass of QxtBasicSTDLoggerEngine.
 */
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
