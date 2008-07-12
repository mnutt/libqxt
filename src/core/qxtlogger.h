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

#ifndef QXTLOGGER_H
#define QXTLOGGER_H

#include "qxtglobal.h"
#include <QObject>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QFlags>
#include "qxtpimpl.h"

class QxtLoggerPrivate;
class QxtLogStream;
class QxtLoggerEngine;

void QxtLoggerMessageHandler(QtMsgType type, const char *msg);

class QXT_CORE_EXPORT QxtLogger : public QObject
{
    Q_OBJECT
    QXT_DECLARE_PRIVATE(QxtLogger);

    // Constructor & Destructor.  Made private as QxtLogger is implemented as a singleton.
    QxtLogger();
    ~QxtLogger();

public:
    /*******************************************************************************
    Defines for a bitmask to enable/disable logging levels.
    Arranged in levels from (assumed) most verbose to most important.
    *******************************************************************************/
    enum LogLevel {
        NoLevels       = 0,     /**< No Levels enabled */
        TraceLevel     = 1<<0,  /**< The most verbose, flags trace() messages to be logged */
        DebugLevel     = 1<<1,  /**< Flags debug() messages to be logged */
        InfoLevel      = 1<<2,  /**< Flags into() messages to be logged */
        WarningLevel   = 1<<3,  /**< Flags warning() messages to be logged */
        ErrorLevel     = 1<<4,  /**< Flags error() messages to be logged */
        CriticalLevel  = 1<<5,  /**< Flags critical() messages to be logged */
        FatalLevel     = 1<<6,  /**< Flags fatal() messages to be logged */
        WriteLevel     = 1<<7,  /**< The most important, flags write() messages to be logged */
        AllLevels      = TraceLevel | DebugLevel | InfoLevel | WarningLevel | ErrorLevel | CriticalLevel | FatalLevel | WriteLevel /**< Enables all log levels */
    };
    Q_DECLARE_FLAGS(LogLevels, LogLevel)

    /* Sone useful things */
    static QString logLevelToString(LogLevel);
    static QxtLogger::LogLevel stringToLogLevel(const QString&);
    static QxtLogger* getInstance();

    void initLoggerEngine(const QString& str_engineName);
    void killLoggerEngine(const QString& str_engineName);

    // Functions to install or remove QxtLogger as a handler for qDebug, qFatal, etc...
    void installAsMessageHandler();
    void removeAsMessageHandler();

    //Functions for adding and removing loggers.
    void addLoggerEngine(const QString& str_engineName, QxtLoggerEngine *ptr_engine);
    void removeLoggerEngine(const QString& str_engineName);
    void removeLoggerEngine(QxtLoggerEngine *rem);
    QxtLoggerEngine* takeLoggerEngine(const QString& take);
    QxtLoggerEngine* engine(const QString& engName);

    // Functions for checking loggers.
    QStringList allLoggerEngines           () const;
    QStringList allEnabledLoggerEngines    () const;
    QStringList allEnabledLoggerEngines    (LogLevel level);
    QStringList allDisabledLoggerEngines   () const;

    bool   isLogLevelEnabled               (const QString& str_engineName, LogLevel level) const;
    bool   isLoggerEngine                  (const QString& str_engineName) const;
    bool   isLoggerEngineEnabled           (const QString& str_engineName) const;

    /*******************************************************************************
    Streaming!
    *******************************************************************************/
    QxtLogStream stream(LogLevel level);
    QxtLogStream trace();
    QxtLogStream debug();
    QxtLogStream info();
    QxtLogStream warning();
    QxtLogStream error();
    QxtLogStream critical();
    QxtLogStream fatal();
    QxtLogStream write();

    /*******************************************************************************
    Log Level enable and disable: The 1-param functions enable/disable that level on
    ALL log engines.  The 2-param functions enable/disable that on a named logger.
    *******************************************************************************/
    void enableLogLevel        (LogLevels level);
    void enableLogLevel        (const QString& str_engineName, LogLevels level);
    void enableAllLogLevels    ();
    void enableAllLogLevels    (const QString& str_engineName);
    void enableLoggerEngine    (const QString& str_engineName);

    void disableLogLevel       (LogLevels level);	
    void disableLogLevel       (const QString& str_engineName, LogLevels level);	
    void disableAllLogLevels   ();
    void disableAllLogLevels   (const QString& str_engineName);	
    void disableLoggerEngine   (const QString& str_engineName);

    void setMinimumLevel       (LogLevel level);
    void setMinimumLevel       (const QString& str_engineName, LogLevel level);

public slots:
    /*******************************************************************************
    Logging Functions: what the QxtLogger is all about.
    *******************************************************************************/
    void info      (const QVariant& message, const QVariant& msg1 = QVariant(),
                    const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
                    const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
                    const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
                    const QVariant& msg8 = QVariant(), const QVariant& msg9 = QVariant());
    void trace     (const QVariant& message, const QVariant& msg1 = QVariant(),
                    const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
                    const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
                    const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
                    const QVariant& msg8 = QVariant(), const QVariant& msg9 = QVariant());
    void warning   (const QVariant& message, const QVariant& msg1 = QVariant(),
                    const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
                    const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
                    const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
                    const QVariant& msg8 = QVariant(), const QVariant& msg9 = QVariant());
    void error     (const QVariant& message, const QVariant& msg1 = QVariant(),
                    const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
                    const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
                    const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
                    const QVariant& msg8 = QVariant(), const QVariant& msg9 = QVariant());
    void debug     (const QVariant& message, const QVariant& msg1 = QVariant(),
                    const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
                    const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
                    const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
                    const QVariant& msg8 = QVariant(), const QVariant& msg9 = QVariant());
    void critical  (const QVariant& message, const QVariant& msg1 = QVariant(),
                    const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
                    const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
                    const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
                    const QVariant& msg8 = QVariant(), const QVariant& msg9 = QVariant());
    void fatal     (const QVariant& message, const QVariant& msg1 = QVariant(),
                    const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
                    const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
                    const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
                    const QVariant& msg8 = QVariant(), const QVariant& msg9 = QVariant());
    void write     (const QVariant& message, const QVariant& msg1 = QVariant(),
                    const QVariant& msg2 = QVariant(), const QVariant& msg3 = QVariant(),
                    const QVariant& msg4 = QVariant(), const QVariant& msg5 = QVariant(),
                    const QVariant& msg6 = QVariant(), const QVariant& msg7 = QVariant(),
                    const QVariant& msg8 = QVariant(), const QVariant& msg9 = QVariant());

    /*******************************************************************************
    Logging Functions in QList<QVariant> form.
    *******************************************************************************/
    void info      (const QList<QVariant>&);
    void trace     (const QList<QVariant>&);
    void warning   (const QList<QVariant>&);
    void error     (const QList<QVariant>&);
    void debug     (const QList<QVariant>&);
    void critical  (const QList<QVariant>&);
    void fatal     (const QList<QVariant>&);
    void write     (const QList<QVariant>&);

    /*******************************************************************************
    And now a generic Logging function
    *******************************************************************************/
    void log       (LogLevel level, const QList<QVariant>& msgList);

signals:
    void loggerAdded(const QString&);
    void loggerRemoved(const QString&);
    void loggerEnabled(const QString&);
    void loggerDisabled(const QString&);

private:
    void setQxtLoggerEngineMinimumLevel    (QxtLoggerEngine *, LogLevel level);
    void directLog                         (LogLevel level, const QList<QVariant>& data);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QxtLogger::LogLevels);
Q_DECLARE_METATYPE(QxtLogger::LogLevel);
Q_DECLARE_METATYPE(QxtLogger::LogLevels);

#define qxtLog QxtLogger::getInstance()

#include "qxtlogstream.h"
#endif // QXTLOGGER_H
