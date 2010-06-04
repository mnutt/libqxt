/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtWeb module of the Qxt library.
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

#include "qxtsshprocess.h"
#include "qxtsshchannel_p.h"


/*!
    \class QxtSshProcess
    \inmodule QxtNetwork
    \brief The QxtSshProcess class allows communication with a process invoked on an SSH server

    QxtSshProcess is an I/O device analogous to QProcess. It can invoke a command or SSH subsystem on
    the SSH server; the stdin, stdout, and stderr channels of the process are redirected through the
    channel.

    QxtSshProcess objects are created using the QxtSshClient::openProcessChannel() method.
*/

/*!
 * \enum QxtSshProcess::TerminalType 
 * \value VanillaTerminal   A terminal with no special features
 * \value Vt102Terminal     A terminal that understands VT102 command codes
 * \value AnsiTerminal      A terminal that understands ANSI command codes
 */

/*! 
 * \fn QxtSshProcess::finished ( int exitCode )
 *
 * This signal is emitted when the process on the SSH server finishes. The parameter is the exit code of
 * the process. After the process has finished, the read buffer QxtSshProcess will still contain any
 * data the process may have written before terminating.
 *
 * Another process or subsystem may be invoked on the same channel after the first process terminates.
 */

/*!
 * \fn QxtSshProcess::started ()
 *
 * This signal is emitted by QxtSshProcess when the remote process has started.
 */

QxtSshProcess::QxtSshProcess(QxtSshClient * parent)
    :QxtSshChannel(parent)
{
    d->openSession();
    connect(this,SIGNAL(connected()),this,SIGNAL(started()));
}
/*!
 * Starts a login shell on the SSH server.
 *
 * If there is already a process running on this channel, the behavior is undefined.
 */
void QxtSshProcess::startShell(){
    d->startShell();
}
/*!
 * Invokes a shell command on the SSH server.
 *
 * If there is already a process running on this channel, the behavior is undefined.
 */
void QxtSshProcess::start(const QString & cmd){
    d->start(cmd);
}
/*!
 * Requests that a PTY be allocated for this channel on the remote host.
 * 
 * This function must be invoked before starting the process that requires it.
 */
void QxtSshProcess::requestPty(TerminalType term){
    switch (term){
        case VanillaTerminal:
            d->requestPty("vanilla");
            break;;
        case Vt102Terminal:
            d->requestPty("vt102");
            break;;
        case AnsiTerminal:
            d->requestPty("ansi");
            break;;
    }
}
