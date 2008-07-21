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

#include "qxttcpconnectionmanager.h"
#include <QTcpSocket>
#include <QtDebug>

/**
 * Constructs a new QxtTcpConnectionManager object with the specified parent.
 */
QxtTcpConnectionManager::QxtTcpConnectionManager(QObject* parent) : QxtAbstractConnectionManager(parent) {
    QXT_INIT_PRIVATE(QxtTcpConnectionManager);
}

QxtTcpConnectionManagerPrivate::QxtTcpConnectionManagerPrivate() : QTcpServer(0) {
    QObject::connect(&mapper, SIGNAL(mapped(QObject*)), this, SLOT(socketDisconnected(QObject*)));
}

void QxtTcpConnectionManagerPrivate::incomingConnection(int socketDescriptor) {
    QIODevice* device = qxt_p().incomingConnection(socketDescriptor);
    if(device) {
        qxt_p().addConnection(device, (quint64)(device));
        mapper.setMapping(device, device);
        QObject::connect(device, SIGNAL(destroyed()), &mapper, SLOT(map()));
        QTcpSocket* sock = qobject_cast<QTcpSocket*>(device);
        if(sock) {
            QObject::connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), &mapper, SLOT(map()));
            QObject::connect(sock, SIGNAL(disconnected()), &mapper, SLOT(map()));
        }
    }
}

/**
 * Listens on the specified interface on the specified port for connections.
 * If \a address is QHostAddress::Any, listens on all interfaces.
 * 
 * Returns true on success; otherwise returns false.
 */
bool QxtTcpConnectionManager::listen(QHostAddress iface, int port)
{
    return qxt_d().listen(iface, port);
}

/**
 * Stops listening for connections. Any connections still open will remain connected.
 */
void QxtTcpConnectionManager::stopListening()
{
    if (!qxt_d().isListening())
    {
        qWarning() << "QxtTcpConnectionManager: Not listening";
        return;
    }
    qxt_d().close();
}

/**
 * This function is called when a new TCP connection becomes available. The parameter
 * is the native socket descriptor for the connection, suitable for use in
 * QTcpSocket::setSocketDescriptor.
 *
 * The default implementation returns a new QTcpSocket with the specified descriptor.
 * Subclasses may return QTcpSocket subclasses, such as QSslSocket.
 */
QIODevice* QxtTcpConnectionManager::incomingConnection(int socketDescriptor) {
    QTcpSocket* device = new QTcpSocket(this);
    device->setSocketDescriptor(socketDescriptior);
    return device;
}

/**
 * \reimp
 */
void QxtTcpConnectionManager::removeConnection(QIODevice* device, quint64 clientID) {
    Q_UNUSED(clientID);
    if(device) {
        device->close();
        delete device;
    }
}

/**
 * Sets an explicit network proxy for the connection manager.
 *
 * \sa QTcpServer::setProxy
 */
void QxtTcpConnectionManager::setProxy(const QNetworkProxy& proxy) {
    qxt_d().setProxy(proxy);
}

/**
 * Returns the proxy in use for the connection manager.
 *
 * \sa QTcpServer::proxy
 */
QNetworkProxy QxtTcpConnectionManager::proxy() const {
    return qxt_d().proxy();
}

void QxtTcpConnectionManagerPrivate::socketDisconnected(QObject* client) {
    qxt_p().disconnect((quint64)(client));
}
