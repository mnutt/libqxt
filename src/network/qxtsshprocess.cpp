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
    \brief The QxtSshProcess class is a channel representing a process to be run on an ssh server.
*/

/*!
 * \enum QxtSshProcess::TerminalType 
 * \value VanillaTerminal
 * \value Vt102Terminal
 * \value AnsiTerminal
 */

/*! 
 * \fn QxtSshProcess::finished ( int exitCode )
 *
 * this signal is emited when the proces on the ssh server has finished with the passed exitCode
 */

/*!
 * \fn QxtSshProcess::started ()
 *
 * this signal is emited when the process on the ssh server has started
 */


QxtSshProcess::QxtSshProcess(QxtSshClient * parent)
    :QxtSshChannel(parent)
{
    d->openSession();
    connect(this,SIGNAL(connected()),this,SIGNAL(started()));
}
/*!
 * start a shell on the ssh server.
 * If there is already a running process, the behaviour is undefined.
 */
void QxtSshProcess::startShell(){
    d->startShell();
}
/*!
 * start a shell command on the ssh server.
 * If there is already a running process, the behaviour is undefined.
 */
 oid QxtSshProcess::start(QString cmd){
    d->start(cmd);
}
/*!
 * allocate a pty for this channel. You must do this _before_ starting a process
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
