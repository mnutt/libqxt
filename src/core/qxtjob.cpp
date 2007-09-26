/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
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

/**
\class QxtJob QxtJob

\ingroup core

\brief Execute a Job on a QThread. once or multiple times.

QxtJob allows easily starting jobs on different threads.\n
exec() will ask for the QThread to run the job on.
The Qthread needs an event loop. 4.3 and later versions of Qt have 
a non virtual QThread with a default event loop, allowing easy deployment of jobs.

\code
QThread thread;
thread.start();
QxtSignalWaiter w1(&thread,SIGNAL(started()));
LockJob().exec(&thread);
\endcode
*/



#include "qxtjob_p.h"
#include <cassert>

QxtJob::QxtJob()
{
    QXT_INIT_PRIVATE(QxtJob);
}

void QxtJob::exec(QThread * onthread)
{
    qxt_d().exec(onthread);
}

void QxtJobPrivate::exec(QThread * onthread)
{
    moveToThread(onthread);
    connect(this,SIGNAL(inwrap_s()),this,SLOT(inwrap_d()));
    emit(inwrap_s());

    mutex.lock();
    assert(waiter.wait(&mutex));
    mutex.unlock();
}
void QxtJobPrivate::inwrap_d()
{
    qxt_p().run();
    emit(qxt_p().done());
    waiter.wakeAll();
}










