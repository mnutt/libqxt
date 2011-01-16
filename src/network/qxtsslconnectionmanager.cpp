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

#include "qxtsslconnectionmanager.h"
#include "qxttcpconnectionmanager_p.h"
#include <QSslKey>

/*!
 * \class QxtSslConnectionManager
 * \inmodule QxtNetwork
 * \brief The QxtSslConnectionManager class accepts SSL connections and maintains a connection pool
 *
 * QxtSslConnectionManager is a standardized interface for accepting and tracking
 * incoming SSL connections.
 *
 * Each incoming connection is assigned an arbitrary, opaque client ID number. This
 * number can be used to retrieve the QSslSocket associated with it. A list of IDs
 * for all current connections can be retrieved with the clients() function.
 *
 * Like QxtSslServer, QxtSslConnectionManager can listen for incoming connections on
 * a specified interface and port. Unlike QTcpServer, but like QxtSslServer,
 * overriding incomingConnection() is not recommended.
 *
 * \sa QxtSslServer, QxtSslConnectionManager
 */

#ifndef QT_NO_OPENSSL

/*!
 * Constructs a new QxtSslConnectionManager object with the specified \a parent.
 */
QxtSslConnectionManager::QxtSslConnectionManager(QObject* parent) : QxtTcpConnectionManager(parent)
{
    // no QXT_INIT_PRIVATE here because we're borrowing QxtTcpConnectionManager's
    setAutoEncrypt(true);
}

void QxtSslConnectionManager::setLocalCertificate(const QSslCertificate& cert)
{
    qxt_d().setLocalCertificate(cert);
}

void QxtSslConnectionManager::setLocalCertificate(const QString& path, QSsl::EncodingFormat format)
{
    qxt_d().setLocalCertificate(path, format);
}

QSslCertificate QxtSslConnectionManager::localCertificate() const
{
    return qxt_d().localCertificate();
}

void QxtSslConnectionManager::setPrivateKey(const QSslKey& key)
{
    qxt_d().setPrivateKey(key);
}

void QxtSslConnectionManager::setPrivateKey(const QString& path, QSsl::KeyAlgorithm algo, QSsl::EncodingFormat format, const QByteArray& passPhrase)
{
    qxt_d().setPrivateKey(path, algo, format, passPhrase);
}

QSslKey QxtSslConnectionManager::privateKey() const
{
    return qxt_d().privateKey();
}

void QxtSslConnectionManager::setAutoEncrypt(bool on)
{
    qxt_d().setAutoEncrypt(on);
}

bool QxtSslConnectionManager::autoEncrypt() const
{
    return qxt_d().autoEncrypt();
}

QIODevice* QxtSslConnectionManager::incomingConnection(int socketDescriptor)
{
    QSslSocket* socket = new QSslSocket(this);
    if(socket->setSocketDescriptor(socketDescriptor)) {
        socket->setLocalCertificate(qxt_d().localCertificate());
        socket->setPrivateKey(qxt_d().privateKey());
        if(qxt_d().autoEncrypt()) socket->startServerEncryption();
        return socket;
    } else {
        delete socket;
        return 0;
    }
}

#endif
