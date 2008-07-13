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

#include "qxtloggerengine.h"

/*! \class QxtLoggerEngine QxtLoggerEngine
    \brief The parent class of all extended Engine Plugins.
    \ingroup QxtCore

    \section Overview
    QxtLoggerEngine is what gives the QxtLogger it's power.  While the Logger itself
    manages memory, logic, and log levels, it is the various Engine Plugins that 
    do the actual work of logging the data.
*/

class QxtLoggerEnginePrivate : public QxtPrivate<QxtLoggerEngine>
{
    QXT_DECLARE_PUBLIC(QxtLoggerEngine);

public:
    QxtLoggerEnginePrivate();

    QxtLogger::LogLevels    bm_logLevel;
    bool                    b_isLogging;
};

QxtLoggerEnginePrivate::QxtLoggerEnginePrivate()
    : bm_logLevel(QxtLogger::AllLevels), b_isLogging(true)
{
}

QxtLoggerEngine::QxtLoggerEngine()
{
    QXT_INIT_PRIVATE(QxtLoggerEngine);
}

QxtLoggerEngine::~QxtLoggerEngine()
{
    QxtLogger::getInstance()->removeLoggerEngine(this);
}

bool QxtLoggerEngine::isLoggingEnabled() const
{
    return qxt_d().b_isLogging;
}

void QxtLoggerEngine::enableLogging()
{
    setLoggingEnabled();
}

void QxtLoggerEngine::disableLogging()
{
    setLoggingEnabled(false);
}

void QxtLoggerEngine::setLoggingEnabled(bool enable)
{
    qxt_d().b_isLogging = enable;
}

void QxtLoggerEngine::setLogLevelsEnabled(QxtLogger::LogLevels levels, bool enable)
{
    if(enable)
    {
        qxt_d().bm_logLevel |= levels;
    }
    else
    {
        qxt_d().bm_logLevel &= ~levels;
    }
}

void QxtLoggerEngine::enableLogLevels(QxtLogger::LogLevels levels)
{
    setLogLevelsEnabled(levels, true);
}

void QxtLoggerEngine::disableLogLevels(QxtLogger::LogLevels levels)
{
    setLogLevelsEnabled(levels, false);
}

bool QxtLoggerEngine::isLogLevelEnabled(QxtLogger::LogLevel level) const
{
    return (qxt_d().bm_logLevel & level);
}
