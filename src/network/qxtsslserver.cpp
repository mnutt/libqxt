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

#include "qxtsslserver.h"
#include <QQueue>
#include <QFile>

/*!
 * \class QxtSslServer
 * \inmodule QxtNetwork
 * \brief The QxtSslServer class provides a simple SSL server.
 *
 * QxtSslServer is a simple SSL server. As a QTcpServer subclass it shares all of the same behaviors
 * as its parent class, except that new connections are created as QSslSocket objects instead of
 * QTcpSocket objects.
 *
 * Before QxtSslServer can accept any encrypted connections, the local certificate (see setLocalCertificate)
 * and private key (see setPrivateKey) must be set. Failure to set these properties before accepting
 * connections will cause all incoming connections to generate sslError signals when negotiating
 * encryption. If autoEncrypt is disabled, the local certificate and private key can be set on the
 * individual socket objects before starting encryption; this behavior is generally not necessary unless
 * you wish to serve up a different certificate based on some property of the connection or some data
 * negotiated before beginning encryption.
 *
 * Unlike QTcpServer, overriding QxtSslServer::incomingConnection() is not recommended.
 *
 * QxtSslServer is only available if Qt was compiled with OpenSSL support.
 */

#ifndef QT_NO_OPENSSL
#include <QSslKey>

class QxtSslServerPrivate : public QxtPrivate<QxtSslServer>
{
public:
    QXT_DECLARE_PUBLIC(QxtSslServer)
    QSslCertificate localCertificate;
    QSslKey privateKey;
    bool autoEncrypt;
    QQueue<QSslSocket*> pendingConnections;
};

/*!
 * Constructs a new QxtSslServer object with the specified \a parent.
 */
QxtSslServer::QxtSslServer(QObject* parent) : QTcpServer(parent)
{
    QXT_INIT_PRIVATE(QxtSslServer);
    qxt_d().autoEncrypt = true;
}

/*!
 * \reimp
 */
bool QxtSslServer::hasPendingConnections() const
{
    return !qxt_d().pendingConnections.isEmpty();
}

/*!
 * \reimp
 */
QTcpSocket* QxtSslServer::nextPendingConnection()
{
    if(!hasPendingConnections()) return 0;
    return qxt_d().pendingConnections.dequeue();
}

/*!
 * Sets the certificate to be presented to clients during the SSL handshake.
 *
 * Setting the certificate only affects new connections established after the certificate
 * has been set. 
 *
 * A certificate is the means of identification used in the SSL process. The local
 * certificate is used by the remote end to verify the local user's identity against its
 * list of Certification Authorities.
 *
 * \sa localCertificate
 * \sa setPrivateKey
 */
void QxtSslServer::setLocalCertificate(const QSslCertificate& cert)
{
    qxt_d().localCertificate = cert;
}

/*!
 * This is an overloaded function, provided for convenience.
 *
 * Sets the certificate to be presented to clients during the SSL handshake to
 * the first certificate contained in the file specified by \a path.
 *
 * \sa localCertificate
 */
void QxtSslServer::setLocalCertificate(const QString& path, QSsl::EncodingFormat format)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) return;
    setLocalCertificate(QSslCertificate(&file, format));
}

/*!
 * Returns the local certificate used to identify the server, or an empty certificate if none has been set.
 * \sa setLocalCertificate
 */
QSslCertificate QxtSslServer::localCertificate() const
{
    return qxt_d().localCertificate;
}

/*!
 * Sets the private key used for encryption.
 *
 * Setting the private key only affects new connections established after the key has been set. 
 *
 * \sa privateKey
 */
void QxtSslServer::setPrivateKey(const QSslKey& key)
{
    qxt_d().privateKey = key;
}

/*!
 * This is an overloaded function, provided for convenience.
 *
 * Sets the private key used for encryption to the key contained in the file specified by
 * \a path. The specified algorithm, format, and pass phrase are used to decrypt the key.
 *
 * \sa privateKey
 */
void QxtSslServer::setPrivateKey(const QString& path, QSsl::KeyAlgorithm algo, QSsl::EncodingFormat format, const QByteArray& passPhrase)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) return;
    setPrivateKey(QSslKey(&file, algo, format, QSsl::PrivateKey, passPhrase));
}

/*!
 * Returns the private key used to encrypt communication, or an empty key if none has been set.
 * \sa setPrivateKey
 */
QSslKey QxtSslServer::privateKey() const
{
    return qxt_d().privateKey;
}

/*!
 * Enables or disables automatically starting encryption on new connections.
 *
 * Set this property to false if you wish to enable encryption on incoming connections
 * at a later time. The default value is true.
 *
 * \sa autoEncrypt
 */
void QxtSslServer::setAutoEncrypt(bool on)
{
    qxt_d().autoEncrypt = on;
}

/*!
 * Returns true if incoming connections will automatically be encrypted, or false otherwise.
 * \sa setAutoEncrypt
 */
bool QxtSslServer::autoEncrypt() const
{
    return qxt_d().autoEncrypt;
}

/*!
 * \reimp
 */
void QxtSslServer::incomingConnection(int socketDescriptor)
{
    QSslSocket* socket = new QSslSocket(this);
    if(socket->setSocketDescriptor(socketDescriptor)) {
        socket->setLocalCertificate(qxt_d().localCertificate);
        socket->setPrivateKey(qxt_d().privateKey);
        if(parent()){
            connect(socket, SIGNAL(sslErrors(const QList<QSslError>&)),
                    parent(), SLOT(sslErrors(const QList<QSslError>&)));
            connect(socket, SIGNAL(peerVerifyError(const QSslError&)),
                    parent(), SLOT(peerVerifyError(const QSslError&)));
        }
        qxt_d().pendingConnections.enqueue(socket);
        // emit newConnection(); // removed: QTcpServerPrivate emits this for us
        if(qxt_d().autoEncrypt) socket->startServerEncryption();
    } else {
        delete socket;
    }
}

#endif /* QT_NO_OPENSSL */
