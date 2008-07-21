/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtNetwork module of the Qxt library.
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
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/

#ifndef QXTTCPCONNECTIONMANAGER_P_H
#define QXTTCPCONNECTIONMANAGER_P_H

#include <qxttcpconnectionmanager.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSignalMapper>

class QxtTcpConnectionManagerPrivate : public QTcpServer, public QxtPrivate<QxtTcpConnectionManager> {
Q_OBJECT
public:
    QxtTcpConnectionManagerPrivate();
    QXT_DECLARE_PUBLIC(QxtTcpConnectionManager);

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void socketDisconnected(QObject* client);

private:
    QSignalMapper disconnectionMapper;
};

#endif
