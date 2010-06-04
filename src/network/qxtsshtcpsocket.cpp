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

#include "qxtsshtcpsocket.h"
#include "qxtsshchannel_p.h"


/*!
    \class QxtSshTcpSocket
    \inmodule QxtNetwork
    \brief The QxtSshTcpSocket class provides a TCP socket tunneled over an SSH connection

    QxtSshTcpSocket enables an SSH client to establish a TCP connection between the SSH server and
    a remote host. Traffic over this TCP connection is tunneled through the channel.

    Note that traffic between the SSH server and the remote host is unencrypted. Only
    communication between QxtSshClient and the SSH server is encrypted.

    QxtSshTcpSocket objects are created using the QxtSshClient::openTcpSocket() method.
*/

/*!
 *
 */
QxtSshTcpSocket::QxtSshTcpSocket(QxtSshClient * parent)
    :QxtSshChannel(parent)
{
}
