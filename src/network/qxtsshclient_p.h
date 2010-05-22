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

#include "qxtsshclient.h"
#include "qxtsshchannel.h"
#include <QTcpSocket>

extern "C"{
#include <libssh2.h>
#include <errno.h>
}

class QxtSshClientPrivate : public QTcpSocket{
    Q_OBJECT
public:
    QxtSshClientPrivate();
    ~QxtSshClientPrivate();
    void d_reset();
    void d_getLastError();

    QxtSshClient * p;
    LIBSSH2_SESSION * d_session;
    LIBSSH2_KNOWNHOSTS * d_knownHosts;
    int d_state;
    QString d_hostName;
    int d_port;
    QxtSshKey  d_hostKey;
    QString d_userName;
    QString d_passphrase;
    QString d_privateKey;
    QString d_publicKey;
    QString d_errorMessage;
    int d_errorCode;
    QxtSshClient::Error d_delaydError;
    QList<QxtSshClient::AuthenticationMethod> d_availableMethods;
    QList<QxtSshClient::AuthenticationMethod> d_failedMethods;
    QxtSshClient::AuthenticationMethod d_currentAuthTry;

    QList<QxtSshChannel*> d_channels;
public slots:
    void d_readyRead();
    void d_connected();
    void d_disconnected();
    void d_channelDestroyed();
    void d_delaydErrorEmit();
};
