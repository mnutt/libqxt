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
#ifndef QXTPOP3_H
#define QXTPOP3_H


#include "qxtglobal.h"
#include "qxtmailmessage.h"
#include "qxtpop3reply.h"
#include "qxtpop3statreply.h"
#include "qxtpop3listreply.h"
#include "qxtpop3retrreply.h"

#include <QObject>
#include <QHostAddress>
#include <QString>
#include <QHash>
#include <QList>
#include <QPair>

class QTcpSocket;
#ifndef QT_NO_OPENSSL
class QSslSocket;
#endif

class QxtPop3Private;
class QXT_NETWORK_EXPORT QxtPop3 : public QObject
{
    Q_OBJECT
public:
    explicit QxtPop3(QObject* parent = 0);

    QByteArray username() const;
    void setUsername(const QByteArray& name);

    QByteArray password() const;
    void setPassword(const QByteArray& password);

    QTcpSocket* socket() const;
    void connectToHost(const QString& hostName, quint16 port = 110);
    void connectToHost(const QHostAddress& address, quint16 port = 110);
    void disconnectFromHost();

    bool startTlsDisabled() const;
    void setStartTlsDisabled(bool disable);

#ifndef QT_NO_OPENSSL
    QSslSocket* sslSocket() const;
    void connectToSecureHost(const QString& hostName, quint16 port = 995);
    void connectToSecureHost(const QHostAddress& address, quint16 port = 995);
#endif

    bool isConnected() const;

    QxtPop3StatReply* stat(int timeout=3000);
    QxtPop3ListReply* messageList(int timeout=100000);
    QxtPop3RetrReply* retrieveMessage(int which, int timeout=300000);
//    QxtPop3Reply* retrieveAll(QList<QxtMailMessage>& list, int timeout=300000);
    QxtPop3Reply* deleteMessage(int which, int timeout=100000);
//    QxtPop3Reply* deleteAll(int timeout=100000);
    QxtPop3Reply* reset(int timeout=10000);
//    QxtPop3TopReply* top(int which, int lines, int timeout=100000);
    QxtPop3Reply* quit(int timeout=3000);

    void clearReplies();


Q_SIGNALS:
    void connected();
    void connectionFailed( const QByteArray & msg );
    void encrypted();
    void encryptionFailed( const QByteArray & msg );
    void authenticated();
    void authenticationFailed( const QByteArray & msg );

    void disconnected();

private:
    QXT_DECLARE_PRIVATE(QxtPop3)
    Q_DISABLE_COPY(QxtPop3)
};

#endif // QXTPOP3_H
