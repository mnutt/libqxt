/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtNetwork module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/


/*!
  \class QxtPop3Command
  \inmodule QxtNetwork
  \brief The QxtPop3Command class encapsulate a POP3 command.

  \sa QxtPop3
 */

#include "qxtpop3command.h"
#include "qxtpop3command_p.h"



QxtPop3Command::QxtPop3Command(int timeout, QObject* parent) : QObject(parent)
{

    QXT_INIT_PRIVATE(QxtPop3Command);
    qxt_d().timeout = timeout;
    qxt_d().status = QxtPop3Command::Pending;
}

QxtPop3Command::Status QxtPop3Command::status() const
{
    return qxt_d().status;
}

QString QxtPop3Command::error() const
{
    return qxt_d().errString;
}

void QxtPop3Command::cancel()
{
    emit finished(Aborted);
}

void QxtPop3Command::setError(const QString& s)
{
    qxt_d().errString = s;
}

void QxtPop3Command::setStatus(const Status s)
{
    qxt_d().status = s;
}

QxtPop3CommandPrivate::QxtPop3CommandPrivate() : QObject(0)
{
}

void QxtPop3CommandPrivate::run()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(timedOut()));
    status = QxtPop3Command::Running;
    timer.start(timeout);
}

void QxtPop3CommandPrivate::timedOut()
{
    status = QxtPop3Command::Timedout;
    emit qxt_p().finished(QxtPop3Command::Timeout);
}
