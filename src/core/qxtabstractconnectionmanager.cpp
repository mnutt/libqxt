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

#include "qxtabstractconnectionmanager.h"
#include <QHash>
#include <QtDebug>

class QxtAbstractConnectionManagerPrivate : public QxtPrivate<QxtAbstractConnectionManager> {
public:
    QHash<quint64, QIODevice*> clients;

    QXT_DECLARE_PUBLIC(QxtAbstractConnectionManager);
};

/**
 * Constructs a QxtAbstractConnection object with the specified parent.
 */
QxtAbstractConnectionManager::QxtAbstractConnectionManager(QObject* parent) : QObject(parent) {
    QXT_INIT_PRIVATE(QxtAbstractConnectionManager);
}

/**
 * \reimp
 */
QxtAbstractConnectionManager::~QxtAbstractConnectionManager() {
    // virtual for subclasses, no need for implementation
}

/**
 * Returns a list of client IDs for all connected clients.
 */
QList<quint64> QxtAbstractConnectionManager::clients() const {
    return qxt_d().clients.keys();
}

/**
 * Returns the QIODevice for the requested client ID.
 */
QIODevice* QxtAbstractConnectionManager::client(quint64 clientID) const {
    return qxt_d().clients.value(clientID, NULL);
}

/**
 * Disconnects the connection with the specified client ID.
 *
 * Implementations should invoke this function when the connection should no longer be
 * used; for instance, when the QIODevice object is destroyed or the connection has been
 * closed. Code that uses the connection manager service should invoke this function to
 * close a connection on demand.
 */
void QxtAbstractConnectionManager::disconnect(quint64 clientID) {
    QIODevice* device = qxt_d().clients.value(clientID, 0);
    if(!device) {
        qWarning() << "QxtAbstractConnectionManager::disconnect: client ID not in use";
        return;
    }
    removeConnection(device, clientID);
    emit disconnected(clientID);
}

/**
 * Begins managing a connection. Each device must have a unique, non-zero client ID, but
 * beyond this constraint implementations may use any convenient value. Implementations
 * should invoke this function after establishing a usable connection and performing any
 * desired initial negotiation.
 *
 * This function will emit the newConnection signal after the internal data structures have
 * been suitably updated.
 */
void QxtAbstractConnectionManager::addConnection(QIODevice* device, quint64 clientID) {
    qxt_d().clients[clientID] = device;
    emit newConnection(device, clientID);
}
