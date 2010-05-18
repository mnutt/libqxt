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
#ifndef QXTPOP3_P_H
#define QXTPOP3_P_H


#include "qxtpop3.h"

#include <QQueue>

class QxtPop3Private : public QObject, public QxtPrivate<QxtPop3>
{
    Q_OBJECT
public:
    QxtPop3Private();

    QXT_DECLARE_PUBLIC(QxtPop3)

    enum Pop3State
    {
        Disconnected,
        StartState,
        Busy,
        Ready
    };

    bool useSecure, disableStartTLS;
    Pop3State state;// rather then an int use the enum.  makes sure invalid states are entered at compile time, and makes debugging easier
    QByteArray buffer, username, password;
    QQueue<QxtPop3Reply*> pending;
    QxtPop3Reply* current;

#ifndef QT_NO_OPENSSL
    QSslSocket* socket;
#else
    QTcpSocket* socket;
#endif

public slots:
    void socketError(QAbstractSocket::SocketError err);
    void disconnected();
    void socketRead();
    void dequeue();
    void terminate(int code);
    void encrypted();
    void authenticated();
};

#endif // QXTPOP3_P_H
