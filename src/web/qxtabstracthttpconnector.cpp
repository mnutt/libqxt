/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtWeb  module of the Qxt library.
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
** <http://www.libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/

/**
\class QxtAbstractHttpConnector QxtAbstractHttpConnector

\ingroup QxtWeb

\brief Base class for defining HTTP-based protocols for use with QxtHttpSessionManager

QxtHttpSessionManager does the work of managing sessions and state for the
otherwise stateless HTTP protocol, but it relies on QxtAbstractHttpConnector
subclasses to implement the protocol used to communicate with the web server.

Subclasses are responsible for accepting new connections (by implementing
listen(const QHostAddress&, quint16) and invoking addConnection(QIODevice*)),
for informing the session manager when request headers are available (by
implementing canParseRequest(const QByteArray&)), for parsing the request
headers (by implementing parseRequest(QByteArray&)), and for writing response
headers (by implementing writeHeaders(QIODevice*, const QHttpResponseHeader&)).

\sa QxtHttpSessionManager
*/

#include "qxthttpsessionmanager.h"
#include "qxtwebcontent.h"
#include <QReadWriteLock>
#include <QHash>
#include <QIODevice>
#include <QByteArray>

#ifndef QXT_DOXYGEN_RUN
class QxtAbstractHttpConnectorPrivate : public QxtPrivate<QxtAbstractHttpConnector> {
public:
    QxtHttpSessionManager* manager;
    QReadWriteLock bufferLock, requestLock;
    QHash<QIODevice*, QByteArray> buffers;  // connection->buffer
    QHash<quint32, QIODevice*> requests;    // requestID->connection
    quint32 nextRequestID;

    inline quint32 getNextRequestID(QIODevice* connection) {
        QWriteLocker locker(&requestLock);
        do {
            nextRequestID++;
            if(nextRequestID == 0xFFFFFFFF) nextRequestID=1;
        } while(requests.contains(nextRequestID));  // yeah, right
        requests[nextRequestID] = connection;
        return nextRequestID;
    }

    inline void doneWithRequest(quint32 requestID) {
        QWriteLocker locker(&requestLock);
        requests.remove(requestID);
    }

    inline QIODevice* getRequestConnection(quint32 requestID) {
        QReadLocker locker(&requestLock);
        return requests[requestID];
    }
};
#endif

/**
 * Creates a QxtAbstractHttpConnector with the specified parent.
 *
 * Note that this is an abstract class and cannot be instantiated directly.
 */
QxtAbstractHttpConnector::QxtAbstractHttpConnector(QObject* parent) : QObject(parent) {
    QXT_INIT_PRIVATE(QxtAbstractHttpConnector);
    qxt_d().nextRequestID = 0;
}

/**
 * \priv
 */
void QxtAbstractHttpConnector::setSessionManager(QxtHttpSessionManager* manager) {
    qxt_d().manager = manager;
}

/**
 * Returns the session manager into which the connector is installed.
 *
 * \sa QxtHttpSessionManager::setConnector
 */
QxtHttpSessionManager* QxtAbstractHttpConnector::sessionManager() const {
    return qxt_d().manager;
}

/**
 * \priv
 * Returns the QIODevice associated with a request ID.
 *
 * The request ID is generated internally and used by the session manager.
 */
QIODevice* QxtAbstractHttpConnector::getRequestConnection(quint32 requestID) {
    return qxt_d().getRequestConnection(requestID);
}

/**
 * Starts managing a new connection.
 *
 * This function should be invoked by a subclass to attach incoming connections
 * to the session manager.
 */
void QxtAbstractHttpConnector::addConnection(QIODevice* device) {
    QWriteLocker locker(&qxt_d().bufferLock);
    qxt_d().buffers[device] = QByteArray();
    QObject::connect(device, SIGNAL(readyRead()), this, SLOT(incomingData()));
    QObject::connect(device, SIGNAL(aboutToClose()), this, SLOT(disconnected()));
    QObject::connect(device, SIGNAL(disconnected()), this, SLOT(disconnected()));
    QObject::connect(device, SIGNAL(destroyed()), this, SLOT(disconnected()));
}

/**
 * \priv
 */
void QxtAbstractHttpConnector::incomingData(QIODevice* device) {
    if(!device) {
        device = qobject_cast<QIODevice*>(sender());
        if(!device) return;
    }
    QReadLocker locker(&qxt_d().bufferLock);
    QByteArray& buffer = qxt_d().buffers[device];
    buffer.append(device->readAll());
    if(!canParseRequest(buffer)) return;
    QHttpRequestHeader header = parseRequest(buffer);
    QxtWebContent* content = 0;
    QByteArray start;
    if(header.contentLength() > 0) {
        start = buffer.left(header.value("content-length").toInt());
        buffer = buffer.mid(header.value("content-length").toInt());
        content = new QxtWebContent(header.contentLength(), start, device);
    } else if(header.hasKey("connection") && header.value("connection").toLower() == "close") {
        start = buffer;
        buffer.clear();
        content = new QxtWebContent(header.contentLength(), start, device);
    } // else no content
    quint32 requestID = qxt_d().getNextRequestID(device);
    sessionManager()->incomingRequest(requestID, header, content);
}

/**
 * \priv
 */
void QxtAbstractHttpConnector::disconnected() {
    QIODevice* device = qobject_cast<QIODevice*>(sender());
    if(!device) return;
    QWriteLocker locker(&qxt_d().bufferLock);
    qxt_d().buffers.remove(device);
    sessionManager()->disconnected(device);
}

/**
 * \fn virtual bool QxtAbstractHttpConnector::listen(const QHostAddress& interface, quint16 port) = 0;
 * Invoked by the session manager to indicate that the connector should listen
 * for incoming connections on the specified interface and port.
 *
 * If the interface is QHostAddress::Any, the server will listen on all network interfaces.
 *
 * Returns true on success, or false if the server could not begin listening.
 *
 * \sa addConnection(QIODevice*)
 */

/**
 * \fn virtual bool QxtAbstractHttpConnector::canParseRequest(const QByteArray& buffer) = 0;
 * Returns true if a complete set of request headers can be extracted from the provided buffer.
 */

/**
 * \fn virtual QHttpRequestHeader QxtAbstractHttpConnector::parseRequest(QByteArray& buffer) = 0;
 * Extracts a set of request headers from the provided buffer.
 *
 * Subclasses implementing this function must be sure to remove the parsed data from the buffer.
 */

/**
 * \fn virtual void QxtAbstractHttpConnector::writeHeaders(QIODevice* device, const QHttpResponseHeader& header) = 0;
 * Writes a set of response headers to the specified device.
 */
