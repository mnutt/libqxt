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

/*!
    \class QxtLogger
    \brief An easy to use, easy to extend logging tool.
    
    \section Overview
    QxtLogger is an easy to use, easy to extend, thread-safe  logging tool.  It was designed to be used "out of the box".
    \code
		#include <QxtLogger>
		...
		QxtLogger::getInstance()->debug("Hi!"); // without using the macro
		qLog->debug("Hi!);	// using the macro
    \endcode
    \see getInstance()

    \section Usage
    QxtLogger is designed to work "out of the box".  The Logger itself is a singleton object that manages all of the logging
    that is requested.  It provides 8 methods to actually log content; they are listed from the most logically verbose to the
    most logically important:
        \li trace()
        \li debug()
        \li info()
        \li warning()
        \li error()
        \li critical()
        \li fatal()
        \li write()
        
    
    These named members only have meaning to the person who uses them.  For example, you could call qLog->Trace() from
    many parts of a complicated, massively recursive function to trace it's output; use qLog->Info() to log that 
    an event such as "Logging has started" has happened; use qLog->Fatal() when an unhandled exception is thrown.  Or,
    you could use qLog->Write() for everything.

    Each of these members comes in two forms: the first takes up to ten QVariants (for moc compatibility), the second
    form takes a QList<QVariant>.  Thus, you can invoke the Info() member in the following ways:

    \code
    // Using the 10-param members.
    qLog->Info(15);
    qLog->Info("I am a test");
    qLog->Info(QTime::currentTime(), "something happened", 3.14);

    // Now with QList<QVariant>
    qLog->Info(QList<QVariant>() << "test" << 15 << QTime::currentTime());
    \endcode

    The real power behind QxtLogger comes from telling it which log levels you actually want to see.  Calling qLog->enableAllLogLevels()
    can give you a lot of data if you need it.  But if you only want to see warnings and errors, qLog->setMinimumLogLevel(WarningLevel) might
    be more useful.


    \section Extending
    The functionality of QxtLogger can be extended by creating plugins derived from QxtLoggerEngine.  Logger Engines
    are the little workers that actually take the raw data, format it, and spit it out into meaningful forms.
*/

#include <QtDebug>
#include <QMutex>
#include <QMutexLocker>
#include "qxtlogger.h"
#include "qxtlogstream.h"
#include "logengines/qxtbasicstdloggerengine.h"
#include "qxtlogger_p.h"

//! \cond
/*******************************************************************************
Constructor for QxtLogger's private data
*******************************************************************************/
QxtLoggerPrivate::QxtLoggerPrivate()
{
    mut_lock = new QMutex(QMutex::Recursive);
}

/*******************************************************************************
Destructor for QxtLogger's private data
*******************************************************************************/
QxtLoggerPrivate::~QxtLoggerPrivate()
{
    Q_FOREACH(QxtLoggerEngine *eng, map_logEngineMap)
    {
        if (eng)
        {
            eng->killLoggerEngine();
            delete eng;
        }
    }
    delete mut_lock;
    mut_lock = NULL;
}

void QxtLoggerPrivate::log(QxtLogger::LogLevel level, const QList<QVariant>& msgList) 
{
    Q_FOREACH(QxtLoggerEngine *eng, map_logEngineMap)
    {
        if (eng && eng->isLoggingEnabled() && eng->isLogLevelEnabled(level))
        {
            eng->writeFormatted(level, msgList);
        }
    }
}
//! \endcond

QxtLoggerEngine     *QxtLogger::engine(const QString &engName)
{
    if (! isLoggerEngine(engName)) return 0;
    else return qxt_d().map_logEngineMap.value(engName);
}

/*! \short Opens a stream to write a message to all Engines with the InfoLevel set.
	The parameterless logging functions return a QxtLogStream for use similar to qDebug().
	\code
	qxtLog->info() << "informational message";
	\endcode
*/
QxtLogStream QxtLogger::info() {
	return stream(QxtLogger::InfoLevel);
}

/*! \short Opens a stream to write a message to all Engines with the TraceLevel set.
	The parameterless logging functions return a QxtLogStream for use similar to qDebug().
	\code
	qxtLog->trace() << "detailed trace message";
	\endcode
*/
QxtLogStream QxtLogger::trace() {
	return stream(QxtLogger::TraceLevel);
}

/*! \short Opens a stream to write a message to all Engines with the ErrorLevel set.
	The parameterless logging functions return a QxtLogStream for use similar to qDebug().
	\code
	qxtLog->error() << "error message";
	\endcode
*/
QxtLogStream QxtLogger::error() {
	return stream(QxtLogger::ErrorLevel);
}

/*! \short Opens a stream to write a message to all Engines with the WarningLevel set.
	The parameterless logging functions return a QxtLogStream for use similar to qDebug().
	\code
	qxtLog->warning() << "warning message";
	\endcode
*/
QxtLogStream QxtLogger::warning() {
	return stream(QxtLogger::WarningLevel);
}

/*! \short Opens a stream to write a message to all Engines with the DebugLevel set.
	The parameterless logging functions return a QxtLogStream for use similar to qDebug().
	\code
	qxtLog->debug() << "debugging log message";
	\endcode
*/
QxtLogStream QxtLogger::debug() {
	return stream(QxtLogger::DebugLevel);
}

/*! \short Opens a stream to write a message to all Engines with the CriticalLevel set.
	The parameterless logging functions return a QxtLogStream for use similar to qDebug().
	\code
	qxtLog->critical() << "critical error message";
	\endcode
*/
QxtLogStream QxtLogger::critical() {
	return stream(QxtLogger::CriticalLevel);
}

/*! \short Opens a stream to write a message to all Engines with the FatalLevel set.
	The parameterless logging functions return a QxtLogStream for use similar to qDebug().
	\code
	qxtLog->fatal() << "fatal error message";
	\endcode
*/
QxtLogStream QxtLogger::fatal() {
	return stream(QxtLogger::FatalLevel);
}

/*! \short Opens a stream to write a message to all Engines with the WriteLevel set.
	The parameterless logging functions return a QxtLogStream for use similar to qDebug().
	\code
	qxtLog->write() << "log message";
	\endcode
*/
QxtLogStream QxtLogger::write() {
	return stream(QxtLogger::WriteLevel);
}


/*! \short Writes a message to all Engines with the InfoLevel set.
	The 10-parameter logging functions are designed to be used with Qt's Signals and Slots, since moc
	currently only accepts functions with up to 10 parameters.  They can take any value that
	QVariant can take as an argument.
*/
void QxtLogger::info(const QVariant &message, const QVariant &msg1, const QVariant &msg2, const QVariant &msg3, const QVariant &msg4, const QVariant &msg5, const QVariant &msg6, const QVariant &msg7, const QVariant &msg8 , const QVariant &msg9 )
{
	QMutexLocker lock(qxt_d().mut_lock);	
	QList<QVariant> vlist;
	vlist.push_back(message);
	if (!msg1.isNull()) vlist.push_back(msg1);
	if (!msg2.isNull()) vlist.push_back(msg2);
	if (!msg3.isNull()) vlist.push_back(msg3);
	if (!msg4.isNull()) vlist.push_back(msg4);
	if (!msg5.isNull()) vlist.push_back(msg5);
	if (!msg6.isNull()) vlist.push_back(msg6);
	if (!msg7.isNull()) vlist.push_back(msg7);
	if (!msg8.isNull()) vlist.push_back(msg8);
	if (!msg9.isNull()) vlist.push_back(msg9);

	info(vlist);	
}


/*! \short Writes a message to all Engines with the TraceLevel set.
	The 10-parameter logging functions are designed to be used with Qt's Signals and Slots, since moc
	currently only accepts functions with up to 10 parameters.  They can take any value that
	QVariant can take as an argument.
*/
void QxtLogger::trace(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8 , const QVariant &msg9 )
{
	QMutexLocker lock(qxt_d().mut_lock);
	QList<QVariant> vlist;
	vlist.push_back(message);
	if (!msg1.isNull()) vlist.push_back(msg1);
	if (!msg2.isNull()) vlist.push_back(msg2);
	if (!msg3.isNull()) vlist.push_back(msg3);
	if (!msg4.isNull()) vlist.push_back(msg4);
	if (!msg5.isNull()) vlist.push_back(msg5);
	if (!msg6.isNull()) vlist.push_back(msg6);
	if (!msg7.isNull()) vlist.push_back(msg7);
	if (!msg8.isNull()) vlist.push_back(msg8);
	if (!msg9.isNull()) vlist.push_back(msg9);

	trace(vlist);
}

/*! \short Writes a message to all Engines with the WarningLevel set.
	The 10-parameter logging functions are designed to be used with Qt's Signals and Slots, since moc
	currently only accepts functions with up to 10 parameters.  They can take any value that
	QVariant can take as an argument.
*/
void QxtLogger::warning(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8 , const QVariant &msg9 )
{
	QMutexLocker lock(qxt_d().mut_lock);
	QList<QVariant> vlist;
	vlist.push_back(message);
	if (!msg1.isNull()) vlist.push_back(msg1);
	if (!msg2.isNull()) vlist.push_back(msg2);
	if (!msg3.isNull()) vlist.push_back(msg3);
	if (!msg4.isNull()) vlist.push_back(msg4);
	if (!msg5.isNull()) vlist.push_back(msg5);
	if (!msg6.isNull()) vlist.push_back(msg6);
	if (!msg7.isNull()) vlist.push_back(msg7);
	if (!msg8.isNull()) vlist.push_back(msg8);
	if (!msg9.isNull()) vlist.push_back(msg9);

	warning(vlist);
}

/*! \short Writes a message to all Engines with the ErrorLevel set.
	The 10-parameter logging functions are designed to be used with Qt's Signals and Slots, since moc
	currently only accepts functions with up to 10 parameters.  They can take any value that
	QVariant can take as an argument.
*/
void QxtLogger::error(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8 , const QVariant &msg9 )
{
	QMutexLocker lock(qxt_d().mut_lock);
	QList<QVariant> vlist;
	vlist.push_back(message);
	if (!msg1.isNull()) vlist.push_back(msg1);
	if (!msg2.isNull()) vlist.push_back(msg2);
	if (!msg3.isNull()) vlist.push_back(msg3);
	if (!msg4.isNull()) vlist.push_back(msg4);
	if (!msg5.isNull()) vlist.push_back(msg5);
	if (!msg6.isNull()) vlist.push_back(msg6);
	if (!msg7.isNull()) vlist.push_back(msg7);
	if (!msg8.isNull()) vlist.push_back(msg8);
	if (!msg9.isNull()) vlist.push_back(msg9);

	error(vlist);
}

/*! \short Writes a message to all Engines with the DebugLevel set.
	The 10-parameter logging functions are designed to be used with Qt's Signals and Slots, since moc
	currently only accepts functions with up to 10 parameters.  They can take any value that
	QVariant can take as an argument.
*/
void QxtLogger::debug(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8 , const QVariant &msg9 )
{
	QMutexLocker lock(qxt_d().mut_lock);
	QList<QVariant> vlist;
	vlist.push_back(message);
	if (!msg1.isNull()) vlist.push_back(msg1);
	if (!msg2.isNull()) vlist.push_back(msg2);
	if (!msg3.isNull()) vlist.push_back(msg3);
	if (!msg4.isNull()) vlist.push_back(msg4);
	if (!msg5.isNull()) vlist.push_back(msg5);
	if (!msg6.isNull()) vlist.push_back(msg6);
	if (!msg7.isNull()) vlist.push_back(msg7);
	if (!msg8.isNull()) vlist.push_back(msg8);
	if (!msg9.isNull()) vlist.push_back(msg9);

	debug(vlist);
}

/*! \short Writes a message to all Engines with the WriteLevel set.
	The 10-parameter logging functions are designed to be used with Qt's Signals and Slots, since moc
	currently only accepts functions with up to 10 parameters.  They can take any value that
	QVariant can take as an argument.
*/
void QxtLogger::write(const QVariant &message, const QVariant &msg1 , const QVariant &msg2, const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8 , const QVariant &msg9 )
{
	QMutexLocker lock(qxt_d().mut_lock);
	QList<QVariant> vlist;
	vlist.push_back(message);
	if (!msg1.isNull()) vlist.push_back(msg1);
	if (!msg2.isNull()) vlist.push_back(msg2);
	if (!msg3.isNull()) vlist.push_back(msg3);
	if (!msg4.isNull()) vlist.push_back(msg4);
	if (!msg5.isNull()) vlist.push_back(msg5);
	if (!msg6.isNull()) vlist.push_back(msg6);
	if (!msg7.isNull()) vlist.push_back(msg7);
	if (!msg8.isNull()) vlist.push_back(msg8);
	if (!msg9.isNull()) vlist.push_back(msg9);

	write(vlist);
}

/*! \short Writes a message to all Engines with the CriticalLevel set.
	The 10-parameter logging functions are designed to be used with Qt's Signals and Slots, since moc
	currently only accepts functions with up to 10 parameters.  They can take any value that
	QVariant can take as an argument.
*/
void QxtLogger::critical(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8 , const QVariant &msg9 )
{
	QMutexLocker lock(qxt_d().mut_lock);
	QList<QVariant> vlist;
	vlist.push_back(message);
	if (!msg1.isNull()) vlist.push_back(msg1);
	if (!msg2.isNull()) vlist.push_back(msg2);
	if (!msg3.isNull()) vlist.push_back(msg3);
	if (!msg4.isNull()) vlist.push_back(msg4);
	if (!msg5.isNull()) vlist.push_back(msg5);
	if (!msg6.isNull()) vlist.push_back(msg6);
	if (!msg7.isNull()) vlist.push_back(msg7);
	if (!msg8.isNull()) vlist.push_back(msg8);
	if (!msg9.isNull()) vlist.push_back(msg9);

	critical(vlist);
}

/*! \short Writes a message to all Engines with the FatalLevel set.
	The 10-parameter logging functions are designed to be used with Qt's Signals and Slots, since moc
	currently only accepts functions with up to 10 parameters.  They can take any value that
	QVariant can take as an argument.
*/
void QxtLogger::fatal(const QVariant &message, const QVariant &msg1 , const QVariant &msg2 , const QVariant &msg3 , const QVariant &msg4 , const QVariant &msg5 , const QVariant &msg6 , const QVariant &msg7 , const QVariant &msg8 , const QVariant &msg9 )
{
	QMutexLocker lock(qxt_d().mut_lock);
	QList<QVariant> vlist;
	vlist.push_back(message);
	if (!msg1.isNull()) vlist.push_back(msg1);
	if (!msg2.isNull()) vlist.push_back(msg2);
	if (!msg3.isNull()) vlist.push_back(msg3);
	if (!msg4.isNull()) vlist.push_back(msg4);
	if (!msg5.isNull()) vlist.push_back(msg5);
	if (!msg6.isNull()) vlist.push_back(msg6);
	if (!msg7.isNull()) vlist.push_back(msg7);
	if (!msg8.isNull()) vlist.push_back(msg8);
	if (!msg9.isNull()) vlist.push_back(msg9);

	fatal(vlist);
}

/*! \short Writes a message to all Engines with the InfoLevel set.
	The 1-parameter logging messages can take any number of arguments in the
	form of a QList<QVariant>, or QList<QVariant>.
*/
void QxtLogger::info(const QList<QVariant> &vlist)
{
	log(QxtLogger::InfoLevel, vlist);
}

/*! \short Writes a message to all Engines with the TraceLevel set.
	The 1-parameter logging messages can take any number of arguments in the
	form of a QList<QVariant>, or QList<QVariant>.
*/
void QxtLogger::trace(const QList<QVariant> &vlist)
{
	log(QxtLogger::TraceLevel, vlist);
}

/*! \short Writes a message to all Engines with the WarningLevel set.
	The 1-parameter logging messages can take any number of arguments in the
	form of a QList<QVariant>, or QList<QVariant>.
*/
void QxtLogger::warning(const QList<QVariant> &vlist)
{
	log(QxtLogger::WarningLevel, vlist);
}

/*! \short Writes a message to all Engines with the ErrorLevel set.
	The 1-parameter logging messages can take any number of arguments in the
	form of a QList<QVariant>, or QList<QVariant>.
*/
void QxtLogger::error(const QList<QVariant> &vlist)
{
	log(QxtLogger::ErrorLevel, vlist);
}

/*! \short Writes a message to all Engines with the DebugLevel set.
	The 1-parameter logging messages can take any number of arguments in the
	form of a QList<QVariant>, or QList<QVariant>.
*/
void QxtLogger::debug(const QList<QVariant> &vlist)
{
	log(QxtLogger::DebugLevel, vlist);
}

/*! \short Writes a message to all Engines with the CriticalLevel set.
	The 1-parameter logging messages can take any number of arguments in the
	form of a QList<QVariant>, or QList<QVariant>.
*/
void QxtLogger::critical(const QList<QVariant> &vlist)
{
	log(QxtLogger::CriticalLevel, vlist);
}

/*! \short Writes a message to all Engines with the FatalLevel set.
	The 1-parameter logging messages can take any number of arguments in the
	form of a QList<QVariant>, or QList<QVariant>.
*/
void QxtLogger::fatal(const QList<QVariant> &vlist)
{
	log(QxtLogger::FatalLevel, vlist);
}

/*! \short Writes a message to all Engines with the WriteLevel set.
	The 1-parameter logging messages can take any number of arguments in the
	form of a QList<QVariant>, or QList<QVariant>.
*/
void QxtLogger::write(const QList<QVariant> &vlist)
{
	log(QxtLogger::WriteLevel, vlist);
}

/*! A Generic Logging Function that takes a LogLevel and a QList<QVariant> of messages

    This function is provided for convenience.
*/
void QxtLogger::log(LogLevel level, const QList<QVariant>& msgList)
{
    /*
    QMutexLocker lock(qxt_d().mut_lock);
    qxt_d().log(level, msgList);
    */
    QMetaObject::invokeMethod(&qxt_d(), "log", Qt::AutoConnection, Q_ARG(QxtLogger::LogLevel, level), Q_ARG(QList<QVariant>, msgList));
}

// \cond
/*******************************************************************************
	Message Handler for qdebug, qerror, qwarning, etc...
	When QxtLogger is enabled as a message handler for Qt, this function
	redirects message calls like qdebug, qwarning, qfatal.
	\see QxtLogger::installAsMessageHandler
	\see QxtLogger::removeAsMessageHandler
*******************************************************************************/
void QxtLoggerMessageHandler(QtMsgType type, const char *msg)
 {
     switch (type) {
     case QtDebugMsg:
	QxtLogger::getInstance()->debug(msg, "qdebug");
        break;
     case QtWarningMsg:
	QxtLogger::getInstance()->warning(msg, "qwarning");
        break;
     case QtCriticalMsg:
	QxtLogger::getInstance()->critical(msg, "qcritical");
        break;
     case QtFatalMsg:
	QxtLogger::getInstance()->fatal(msg, "qfatal");
	abort();
     }
 }
// \endcond

/*! \short Installs QxtLogger as Qt's message handler.
	This will make Qt macros use QxtLogger instead of the default
	mechanism:
		\li qDebug()
		\li qWarning()
		\li qCritical()
		\li qFatal() will call abort() and terminate your application.
*/
 void QxtLogger::installAsMessageHandler()
 {
	 QMutexLocker lock(qxt_d().mut_lock);
	 qInstallMsgHandler(QxtLoggerMessageHandler);
 }

 /*! \short Tells Qt to use it's own message handling again.
 */
 void QxtLogger::removeAsMessageHandler()
 {
	 QMutexLocker lock(qxt_d().mut_lock);
	 qInstallMsgHandler(0);
 }

// \cond
 /*****************************************************************************
	Constructor
	Private, since QxtLogger is a singleton.
 *****************************************************************************/
QxtLogger::QxtLogger()
{
    QXT_INIT_PRIVATE(QxtLogger);
    qRegisterMetaType<QxtLogger::LogLevel>();
    qRegisterMetaType<QxtLogger::LogLevels>();
    addLoggerEngine("DEFAULT", new QxtBasicSTDLoggerEngine);
    setMinimumLevel("DEFAULT", QxtLogger::InfoLevel);
}

/***************************************************************************//**
	Destructor.
	The Destructor for QxtLogger iterates through all the currently installed
	QxtLoggerEngines, calls their killLoggerEngine functions through QxtLoggerEngine::killLoggerEngine(), 
	and then deletes them from the map.
*******************************************************************************/
QxtLogger::~QxtLogger()
{
    // implicit destruction only
}
// \endcond

/*!	\short Returns a pointer to the instance of the Logger
	QxtLogger is implemented as a singleton, a single object, that
	manages all of the logging done in an application.  The easiest way
	to use it is by calling the qLog macro:

	\code
	#include <QxtLogger>
	...
	qLog->info("I can log things!");
	\endcode

	qLog expands to QxtLogger::getInstance, which returns a pointer to the logger.

	QxtLogger manages it's own memory, so please remember the second rule of pointers:
	don't delete it unless you instantiated it yourself.
	\code
	delete qLog // Will horribly crash your app, and possibly your system
	\endcode

*/
QxtLogger *QxtLogger::getInstance()
{
	static QxtLogger objectInstance;
	return &objectInstance;
}

/*! \short Returns a QString of the given LogLevel
	This function is provided for convenience.
	*/
QString QxtLogger::logLevelToString(LogLevel l)
{
    if (l == TraceLevel) return "TraceLevel";
    if (l == DebugLevel) return "DebugLevel";
    if (l == InfoLevel) return "InfoLevel";
    if (l == WarningLevel) return "WarningLevel";
    if (l == ErrorLevel) return "ErrorLevel";
    if (l == CriticalLevel) return "CriticalLevel";
    if (l == FatalLevel) return "FatalLevel";
    if (l == WriteLevel) return "WriteLevel";
    if (l == AllLevels) return "AllLevels";
    return "NoLevels";    
}

/*! \short Returns a LogLevel for the given string, or QxtLogger::NoLevels if invalid.
	This function is provided for convenience.
 */
QxtLogger::LogLevel QxtLogger::stringToLogLevel(const QString& a)
{
         if (a.toLower() == "alllevels") return QxtLogger::AllLevels;
         else if  (a.toLower() == "writelevel") return QxtLogger::TraceLevel;
         else if  (a.toLower() == "fatallevel") return QxtLogger::DebugLevel;
         else if  (a.toLower() == "criticallevel") return QxtLogger::InfoLevel;
         else if  (a.toLower() == "errorlevel") return QxtLogger::WarningLevel;
         else if  (a.toLower() == "warnlevel") return QxtLogger::ErrorLevel;
         else if  (a.toLower() == "infolevel") return QxtLogger::CriticalLevel;
         else if  (a.toLower() == "debuglevel") return QxtLogger::FatalLevel;
         else if  (a.toLower() == "tracelevel") return QxtLogger::WriteLevel;
         else return QxtLogger::NoLevels;
}

/*! \short Enables the given LogLevels across all Engines.
	\code
	qLog->enableLogLevel(QxtLogger::NoLevels);
	qLog->write("I don't do anything!");
	qLog->enableLogLevel(QxtLogger::AllLevels);
	qLog->write("Hi there!");
	\endcode
	\param level   A bitmask of LogLevels
*/
void QxtLogger::enableLogLevel(LogLevels level)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if(qxt_d().map_logEngineMap.empty()) return;

	Q_FOREACH(QxtLoggerEngine *eng, qxt_d().map_logEngineMap)
	{
		if (eng)
		{
			eng->enableLogLevel(level);
		}
	}

}

/*! \short Returns a reference to a refcounted stream.
	This is still in its early phases and is in dire need of testing and debugging.
	\code
	QxtLogger::stream(QxtLogger::WriteLevel) << "This should write stuff" << 1.5 << QString();
	\endcode
*/
QxtLogStream QxtLogger::stream(LogLevel level)
{
	return QxtLogStream(this, level, QList<QVariant>());
}

/*! \short Enables the given LogLevels on a named Engine
	This will use the given engine name to tell a loaded QxtLoggerEngine
	what LogLevels it should enable.
	\code
	qLog->addLoggerEngine("test", "libTestLogger");
	qLog->enableLogLevel("test", QxtLoger::AllLevels);
	qLog->write("You can see me through your 'test' logger now!");
	\endcode

	\param str_engineName	The name of a QxtLoggerEngine.
	\param level			A LogLevel or LogLevels to enable.
	\see addLoggerEngine()
*******************************************************************************/
void QxtLogger::enableLogLevel(const QString &str_engineName, LogLevels level)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (qxt_d().map_logEngineMap.contains(str_engineName))
	{
		if (qxt_d().map_logEngineMap.value(str_engineName))
		{
			qxt_d().map_logEngineMap.value(str_engineName)->enableLogLevel(level);
		}
	}
}
/*! \short Turns on all log levels for a named engine.
	This is a function provided for convenience, and is equivalent to
	calling:
	\code
	qLog->enableLogLevel("test", QxtLogger::AllLevels);
	\endcode
*/
void QxtLogger::enableAllLogLevels(const QString &str_engineName)
{
	enableLogLevel(str_engineName, QxtLogger::AllLevels);
}

/*! \short Turns on all log levels for all engines.
	This is a function provided for convenience, and is equivalent to
	calling:
	\code
	qLog->enableLogLevel(QxtLogger::AllLevels);
	\endcode
*/
void QxtLogger::enableAllLogLevels()
{
	enableLogLevel(QxtLogger::AllLevels);
}

/*! \short Enables a named engine if it is currently disabled.
	\param str_engineName the name of a QxtLoggerEngine.
	*/
void QxtLogger::enableLoggerEngine(const QString &str_engineName)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (qxt_d().map_logEngineMap.contains(str_engineName))
	{
		if (qxt_d().map_logEngineMap.value(str_engineName))
		{
			qxt_d().map_logEngineMap.value(str_engineName)->enableLogging();
			emit loggerEnabled(str_engineName);
		}
	}
}

/*! \short Unflags the given LogLevels across all Engines.
	Disables the given LogLevel across all QxtLoggersEngines.  Note that some

	\param level A LogLevel or LogLevels to disable.
*/
void QxtLogger::disableLogLevel(LogLevels level)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if(qxt_d().map_logEngineMap.empty()) return;
	Q_FOREACH(QxtLoggerEngine *eng, qxt_d().map_logEngineMap)
	{
		if (eng)
		{
			eng->disableLogLevel(level);
		}
	}
}


/*! \short Disables the named Engine
	Disables the the named QxtLoggerEngine if it exists.

	\param str_engineName The name of a log Engine to disable.
*/
void QxtLogger::disableLoggerEngine(const QString &str_engineName)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (qxt_d().map_logEngineMap.contains(str_engineName))
	{
		if (qxt_d().map_logEngineMap.value(str_engineName))
		{
			qxt_d().map_logEngineMap.value(str_engineName)->disableLogging();
			emit loggerDisabled(str_engineName);
		}
	}
}

/*! \short Sets the minimumlog level for all Engines, as well as the levels above it. 
	\param level The single LogLevel to set as minimum.
*/
void QxtLogger::setMinimumLevel(LogLevel level)
{
	QMutexLocker lock(qxt_d().mut_lock);
	Q_FOREACH(QxtLoggerEngine *eng, qxt_d().map_logEngineMap)
	{
		if (eng)
		{
			setQxtLoggerEngineMinimumLevel(eng, level);
		}
	}
}

/*! \short Sets the minimumlog level for the named Engine, as well as the levels above it. 
	\param str_engineName The name of a QxtLoggerEngine.
	\param level The single LogLevel to set as minimum.
*/
void QxtLogger::setMinimumLevel(const QString &str_engineName, LogLevel level)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (qxt_d().map_logEngineMap.contains(str_engineName))
	{
		if (qxt_d().map_logEngineMap.value(str_engineName))
		{
			setQxtLoggerEngineMinimumLevel(qxt_d().map_logEngineMap.value(str_engineName), level);
		}
	}
}

/*! \short Calls QxtLoggerEngine::initialize() for the named Engine 
	Some QxtLoggerEngine plugins might require additional initialization.  Check the documentation
	for your plugin.  Most basic plugins will not require special tasks.
	\param str_engineName The name of a QxtLoggerEngine.
*/
void QxtLogger::initLoggerEngine(const QString &str_engineName)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (qxt_d().map_logEngineMap.contains(str_engineName))
	{
		if (qxt_d().map_logEngineMap.value(str_engineName))
		{
			qxt_d().map_logEngineMap.value(str_engineName)->initLoggerEngine();
		}
	}
}

/*! \short Calls QxtLoggerEngine::kill() for the named Engine 
	Some QxtLoggerEngine plugins might require special cleanup before destruction.
	Check the documentation	for your plugin.  Most basic plugins will not require this.
	\param str_engineName The name of a QxtLoggerEngine.
*/
void QxtLogger::killLoggerEngine(const QString &str_engineName)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (qxt_d().map_logEngineMap.contains(str_engineName))
	{
		if (qxt_d().map_logEngineMap.value(str_engineName))
		{
			qxt_d().map_logEngineMap.value(str_engineName)->killLoggerEngine();
		}
	}
}
/*! \short Checks if the named Engine has the given LogLevel enabled.
	\param str_engineName  The name of a QxtLoggerEngine to query
	\param level           A LogLevel or LogLevels to disable.
	\ret                   Returns true or false.
*/
bool QxtLogger::isLogLevelEnabled  (const QString &str_engineName, LogLevel level) const
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (qxt_d().map_logEngineMap.contains(str_engineName))
	{
		return qxt_d().map_logEngineMap.value(str_engineName)->isLogLevelEnabled(level);
	}
	else return false;
}

/*! \short	Disables the given LogLevel across the named QxtLoggersEngines.
	\param str_engineName	The name of a QxtLoggerEngine.
	\param level			A LogLevel or LogLevels to disable.
*/
void QxtLogger::disableLogLevel(const QString &str_engineName, LogLevels level)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (qxt_d().map_logEngineMap.contains(str_engineName))
	{
		if (qxt_d().map_logEngineMap.value(str_engineName))
		{
			qxt_d().map_logEngineMap.value(str_engineName)->disableLogLevel(level);
		}
	}
}

/*! \short Disables all log levels for the named Engine.
	\param str_engineName The name of an Engine.
*/
void QxtLogger::disableAllLogLevels(const QString &str_engineName)
{
	disableLogLevel(str_engineName, QxtLogger::AllLevels);
}

/*! \short Disables all log levels for all named Engines.
*/
void QxtLogger::disableAllLogLevels()
{
	disableLogLevel(QxtLogger::AllLevels);
}

/*! \short Gives QxtLogger an already-instantiated QxtLoggerEngine to use.
	addLoggerEngine inserts a subclass of QxtLoggerEngine for QxtLogger
        to manage.  QxtLogger takes ownership of the engine and will
        manage memory on its own.
	\code
	#include <QxtLogger>
	...
	class MyLoggerEngine : public QxtLoggerEngine;
	...
	qLog->addLoggerEngine("my engine", new MyLoggerEngine);
	\endcode
	\see QxtLoggerEngine
*/
void QxtLogger::addLoggerEngine(const QString &str_engineName, QxtLoggerEngine *ptr_engine)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (!qxt_d().map_logEngineMap.contains(str_engineName) && ptr_engine)
	{
		qxt_d().map_logEngineMap.insert(str_engineName, ptr_engine);
		emit loggerAdded(str_engineName);
	}
}

/*
 \short Gives QxtLogger an already-instantiated QLibrary.
	This is an overloaded functionand not the preferred method of adding Engines.
	It is useful to load plugins that are not in the applications Path.
	\code
	QLibrary *lib = new QLibrary("/path/to/plugin");
	qLog->addLogger("my engine", lib);
	\endcode

void QxtLogger::addLoggerEngine(const QString &str_engineName, QLibrary *ptr_engineLib)
{
	QMutexLocker lock(qxt_d().mut_lock);
	typedef QxtLoggerEngine* (*LibInstance)();
	LibInstance instance = (LibInstance)ptr_engineLib->resolve("getInstance");
	qWarning() << ptr_engineLib->errorString();

	if (!instance) return;
	else if (!qxt_d().map_logEngineMap.contains(str_engineName) && ptr_engineLib)
	{
		qxt_d().map_logEngineMap.insert(str_engineName, instance());
		emit loggerAdded(str_engineName);
	}
}

 \short Loads an Engine from a plugin in the current path.
	\code
	qLog->addLogger("my lib", "libQxtSomeKindOfLoggerEngine");
	\endcode
	\param str_engineName The name to give this QxtLoggerEngine.
	\param str_libName The name of the library to load.

void QxtLogger::addLoggerEngine(const QString &str_engineName, const QString &str_libName)
{
	QLibrary engineLib(str_libName);

        addLoggerEngine(str_engineName, &engineLib);
}
*/
/*! \short Remove the named Engine from use.
*/
void QxtLogger::removeLoggerEngine(const QString &str_engineName)
{
	QMutexLocker lock(qxt_d().mut_lock);
	QxtLoggerEngine* eng = takeLoggerEngine(str_engineName);
	if(!eng) return;
	eng->killLoggerEngine();
	delete eng;
}

void QxtLogger::removeLoggerEngine(QxtLoggerEngine *rem)
{
	QMutexLocker lock(qxt_d().mut_lock);
	Q_FOREACH (QString i, this->qxt_d().map_logEngineMap.keys(rem))
	{
		takeLoggerEngine(i); // return value ignored
	}
}

QxtLoggerEngine *QxtLogger::takeLoggerEngine(const QString &str)
{
	QMutexLocker lock(qxt_d().mut_lock);
	QxtLoggerEngine *eng = qxt_d().map_logEngineMap.take(str);
	if(!eng) return NULL;
	emit loggerRemoved(str);
	return eng;
}

/*! \short Retuns a QStringList containing the namnes of all loaded Engines being managed by QxtLogger.
	\ret QStringList engine names.
*/
QStringList QxtLogger::allLoggerEngines() const
{
	QMutexLocker lock(qxt_d().mut_lock);
	return qxt_d().map_logEngineMap.keys();
}

/*! \short Retuns a QStringList containing the namnes of all loaded Engines that are currently enabled.
	\ret QStringList engine names.
*/
QStringList QxtLogger::allEnabledLoggerEngines() const
{
	QMutexLocker lock(qxt_d().mut_lock);
	QStringList sl_engineNames = qxt_d().map_logEngineMap.keys();
	QStringList result;
	Q_FOREACH(QString str_name, sl_engineNames)
	{
		if (qxt_d().map_logEngineMap.value(str_name)->isLoggingEnabled()) result.append(str_name);
	}
	return result;
}

/*! \short Retuns a QStringList containing the namnes of all loaded Engines that are currently disabled.
	\ret QStringList engine names.
*/
QStringList QxtLogger::allDisabledLoggerEngines	() const
{
	QMutexLocker lock(qxt_d().mut_lock);
	QStringList sl_engineNames = qxt_d().map_logEngineMap.keys();
	QStringList result;
	Q_FOREACH(QString str_name, sl_engineNames)
	{
		if (!qxt_d().map_logEngineMap.value(str_name)->isLoggingEnabled()) result.append(str_name);
	}
	return result;
}

/*! \short Checks if the given string names a currently loaded Engine.
	\ret True or false.
*/
bool QxtLogger::isLoggerEngine	(const QString &str_engineName) const
{
	QMutexLocker lock(qxt_d().mut_lock);
	return qxt_d().map_logEngineMap.contains(str_engineName);
}

/*! \short Checkes if the named engine is currently enabled
	\ret True or false
*/
bool QxtLogger::isLoggerEngineEnabled			(const QString &str_engineName) const
{
	QMutexLocker lock(qxt_d().mut_lock);
	return (qxt_d().map_logEngineMap.contains(str_engineName) && qxt_d().map_logEngineMap.value(str_engineName)->isLoggingEnabled());
}

//! \cond
void QxtLogger::setQxtLoggerEngineMinimumLevel(QxtLoggerEngine * eng, LogLevel level)
{
	QMutexLocker lock(qxt_d().mut_lock);
	if (!eng) return; 
	(QxtLogger::TraceLevel    < level) ? eng->disableLogLevel(QxtLogger::TraceLevel)    : eng->enableLogLevel(QxtLogger::TraceLevel);
	(QxtLogger::DebugLevel    < level) ? eng->disableLogLevel(QxtLogger::DebugLevel)    : eng->enableLogLevel(QxtLogger::DebugLevel);
	(QxtLogger::InfoLevel     < level) ? eng->disableLogLevel(QxtLogger::InfoLevel)     : eng->enableLogLevel(QxtLogger::InfoLevel);
	(QxtLogger::WarningLevel     < level) ? eng->disableLogLevel(QxtLogger::WarningLevel)     : eng->enableLogLevel(QxtLogger::WarningLevel);
	(QxtLogger::ErrorLevel    < level) ? eng->disableLogLevel(QxtLogger::ErrorLevel)    : eng->enableLogLevel(QxtLogger::ErrorLevel);
	(QxtLogger::CriticalLevel < level) ? eng->disableLogLevel(QxtLogger::CriticalLevel) : eng->enableLogLevel(QxtLogger::CriticalLevel);
	(QxtLogger::FatalLevel    < level) ? eng->disableLogLevel(QxtLogger::FatalLevel)    : eng->enableLogLevel(QxtLogger::FatalLevel);
	(QxtLogger::WriteLevel    < level) ? eng->disableLogLevel(QxtLogger::WriteLevel)    : eng->enableLogLevel(QxtLogger::WriteLevel);
}
//! \endcond

