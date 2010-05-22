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
#include "qxtsshclient_p.h"
#include "qxtsshchannel.h"

class QxtSshChannelPrivate : public QObject{
public:
    QxtSshChannelPrivate(QxtSshChannel*,QxtSshClient *);
    QxtSshChannel * p;
    QxtSshClient * d_client;
    LIBSSH2_CHANNEL * d_channel;
    LIBSSH2_SESSION * d_session;
    int d_read_stream_id;
    int d_write_stream_id;

    int d_state;
    bool activate();

    QList<int> d_next_actions;
    QString d_cmd;
    QByteArray d_pty;
    void openSession();
    void requestPty(QByteArray pty);
    void start(QString cmd);
    void startShell();

    void openTcpSocket(QString host,qint16 port);
    QString d_host;
    qint16 d_port;
};
