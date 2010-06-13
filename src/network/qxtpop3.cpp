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


/*!
  \class QxtPop3
  \inmodule QxtNetwork
  \brief The QxtPop3 class implements a POP3 client.

  Implements the IETF standard 53  http://www.faqs.org/rfcs/std/std53.html

  The API is asynchronous: when calling a POP3 method, the call returns immediately and
  one gets a pointer to a QxtPop3Reply, that can be used to get feedback
  (typically connect its finished() signal to some slot handling the result, and get
   the result of the command once finished, if applicable).
 */

#include "qxtpop3.h"
#include "qxtpop3_p.h"
#include "qxtpop3reply_p.h"

#include <QTcpSocket>
#include <QNetworkInterface>
#ifndef QT_NO_OPENSSL
#    include <QSslSocket>
#endif





QxtPop3Private::QxtPop3Private() : QObject(0), disableStartTLS(false)
{
    // empty ctor
}

/*!
  Constructs a new QxtPop3 whith parent \a parent.
 */
QxtPop3::QxtPop3(QObject* parent) : QObject(parent)
{
    QXT_INIT_PRIVATE(QxtPop3);
    qxt_d().state = QxtPop3Private::Disconnected;
#ifndef QT_NO_OPENSSL
    qxt_d().socket = new QSslSocket(this);
    QObject::connect(socket(), SIGNAL(encrypted()), this, SIGNAL(encrypted()));
    QObject::connect(socket(), SIGNAL(encrypted()), &qxt_d(),SLOT(encrypted()));
#else
    qxt_d().socket = new QTcpSocket(this);
#endif
    QObject::connect(socket(), SIGNAL(connected()), this, SIGNAL(connected()));
    QObject::connect(socket(), SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    QObject::connect(socket(), SIGNAL(disconnected()), &qxt_d(), SLOT(disconnected()));
    QObject::connect(socket(), SIGNAL(error(QAbstractSocket::SocketError)), &qxt_d(), SLOT(socketError(QAbstractSocket::SocketError)));
    QObject::connect(socket(), SIGNAL(readyRead()), &qxt_d(), SLOT(socketRead()));
}

/*!
  Returns the connection's user name; it may be empty.
 */
QByteArray QxtPop3::username() const
{
    return qxt_d().username;
}

/*!
  Sets the connection's user name to \a username. To have effect, the user name must be set \bold{before} the connection is opened.
  Alternatively, you can quit(), set the user name, and call connectToHost() again.
  */
void QxtPop3::setUsername(const QByteArray& username)
{
    qxt_d().username = username;
}

/*!
  Returns the connection's password; it may be empty.
 */
QByteArray QxtPop3::password() const
{
    return qxt_d().password;
}

/*!
  Sets the connection's password to \a password. To have effect, the password must be set \bold{before} the connection is opened.
  Alternatively, you can quit(), set the password, and call connectToHost() again.
  */
void QxtPop3::setPassword(const QByteArray& password)
{
    qxt_d().password = password;
}

/*!
  Returns a pointer to the socket used for the connection to the server.
  */
QTcpSocket* QxtPop3::socket() const
{
    return qxt_d().socket;
}

/*!
  Opens a connection to the server \a hostName on \a port.
  Authentication is performed, and startTLS is sent if enabled (else the connection isn't encrypted).

  \sa connectToSecureHost(), disconnectFromHost(), startTlsDisabled()
 */
void QxtPop3::connectToHost(const QString& hostName, quint16 port)
{
    qxt_d().useSecure = false;
    qxt_d().state = QxtPop3Private::StartState;
    socket()->connectToHost(hostName, port);
}

/*!
  Overloaded function.
 */
void QxtPop3::connectToHost(const QHostAddress& address, quint16 port)
{
    connectToHost(address.toString(), port);
}

/*!
  Closes the connection.
 */
void QxtPop3::disconnectFromHost()
{
    socket()->disconnectFromHost();
}

/*!
  Returns \c true if startTLS is disabled, \c false if it is enabled.
  Default value is \c false (startTLS enabled).
  */
bool QxtPop3::startTlsDisabled() const
{
    return qxt_d().disableStartTLS;
}

/*!
  Disable the startTLS method if \a disable is \c true, enables it if it is \c false.
  */
void QxtPop3::setStartTlsDisabled(bool disable)
{
    qxt_d().disableStartTLS = disable;
}

#ifndef QT_NO_OPENSSL
/*!
  Returns a pointer to the SSL socket used for the connection to the server.
  \sa socket()
  */
QSslSocket* QxtPop3::sslSocket() const
{
    return qxt_d().socket;
}

/*!
  Opens a SSL connection to the server \a hostName on \a port.
  \sa connectToHost()
 */
void QxtPop3::connectToSecureHost(const QString& hostName, quint16 port)
{
    qxt_d().useSecure = true;
    qxt_d().state = QxtPop3Private::StartState;
    sslSocket()->connectToHostEncrypted(hostName, port);
}

/*!
  Overloaded function.
 */
void QxtPop3::connectToSecureHost(const QHostAddress& address, quint16 port)
{
    connectToSecureHost(address.toString(), port);
}
#endif // QT_NO_OPENSSL

/*!
  Returns \c true if the client is connected to the server, \c false otherwise.
  */
bool QxtPop3::isConnected() const
{
    return qxt_d().state != QxtPop3Private::Disconnected;
}

/*!
   Implement the STAT POP3 command.
   When the command is completed, the message count in the mailbox and total size in bytes can be retrieved
   via the count() and size() methods of the QxtPop3StatReply object returned.
 */
QxtPop3StatReply* QxtPop3::stat(int timeout)
{
    QxtPop3StatReply* reply = new QxtPop3StatReply(timeout, this);
    qxt_d().pending.enqueue(reply);
    qxt_d().dequeue();
    return reply;
}

/*!
   Implement the LIST POP3 command.
   When the command is completed, the result can be read from the QxtPop3ListReply object returned.
 */
QxtPop3ListReply* QxtPop3::messageList(int timeout)
{
    QxtPop3ListReply* reply = new QxtPop3ListReply(timeout, this);
    qxt_d().pending.enqueue(reply);
    qxt_d().dequeue();
    return reply;
}

/*!
   Retrieve message nb \a which.
   When the command is completed, the result can be read from the QxtPop3RetrReply object returned.
 */
QxtPop3RetrReply* QxtPop3::retrieveMessage(int which, int timeout)
{
    QxtPop3RetrReply* reply = new QxtPop3RetrReply(which, timeout, this);
    qxt_d().pending.enqueue(reply);
    qxt_d().dequeue();
    return reply;
}

//QxtPop3Reply* QxtPop3::retrieveAll(QList<QxtMailMessage>& list, int timeout)
//{
//
//}

/*!
   Delete the message nb \a which.
   Until the session is closed, the message can be undeleted by a reset.
 */
QxtPop3Reply* QxtPop3::deleteMessage(int which, int timeout)
{
    QxtPop3DeleReply* reply = new QxtPop3DeleReply(which, timeout, this);
    qxt_d().pending.enqueue(reply);
    qxt_d().dequeue();
    return reply;
}

//QxtPop3Reply* QxtPop3::deleteAll(int timeout)
//{
//
//}

/*!
  Reset the session. All messages marked as deleted are undeleted.
 */
QxtPop3Reply* QxtPop3::reset(int timeout)
{
    QxtPop3ResetReply* reply = new QxtPop3ResetReply(timeout, this);
    qxt_d().pending.enqueue(reply);
    qxt_d().dequeue();
    return reply;
}

//QxtPop3TopReply* QxtPop3::top(int which, int lines, QStringList*& top, int timeout)
//{
//
//}

/*!
  Close the session, and disconnect from the server.
 */
QxtPop3Reply* QxtPop3::quit(int timeout)
{
    QxtPop3QuitReply* reply = new QxtPop3QuitReply(timeout, this);
    qxt_d().pending.enqueue(reply);
    qxt_d().dequeue();
    return reply;
}

/*!
  Deletes all finished replies in the queue. Run this to free memory when you don't need
  to access the finished replies anymore (to get results for example). A good moment to do
  this is after closing the connection to the server, if you keep the QxtPop3 object for later
  connections (when the QxtPop3 object is deleted, all replies associated to it are deleted
  automatically).
  */
void QxtPop3::clearReplies()
{
    foreach(QxtPop3Reply* reply, qxt_d().pending)
    {
        switch(reply->status())
        {
        case QxtPop3Reply::Completed:
        case QxtPop3Reply::Timedout:
        case QxtPop3Reply::Error:
            delete reply;
            break;
        default:
            break;
        }
    }
}

/*!
  \fn QxtPop3::connected()

  Emitted once the connection to the server is established.
  */

/*!
  \fn QxtPop3::connectionFailed( const QByteArray & msg )

  Emitted when the connection fails, \a msg containing a description of the failure.
  */

/*!
  \fn QxtPop3::encrypted()

  Emitted when the SSL negotiation succeeds, and the connection becomes encrypted
  (either from start, with connectToSecureHost(), or after the startTLS method is used).
  */

/*!
  \fn QxtPop3::encryptionFailed( const QByteArray & msg )

  Emitted if the SSL negotiation fails, \a msg holding a desription of the cause of the failure.
  */

/*!
  \fn QxtPop3::authenticated()

  Emitted when the connections becomes authenticated.
  */

/*!
  \fn QxtPop3::authenticationFailed( const QByteArray & msg )

  Emitted if the authentication fails, \a msg holding a desription of the cause of the failure.
  */


/*!
  \fn QxtPop3::disconnected()

  Emitted when the client is disconnected from the server.
  */

void QxtPop3Private::socketError(QAbstractSocket::SocketError err)
{
    if (err == QAbstractSocket::SslHandshakeFailedError)
    {
        emit qxt_p().encryptionFailed( socket->errorString().toAscii() );
        if (current != 0) current->cancel();
    }
    else if (state == StartState)
    {
        emit qxt_p().connectionFailed( socket->errorString().toAscii() );
    }
}

void QxtPop3Private::disconnected()
{
    state = Disconnected;
}

void QxtPop3Private::socketRead()
{
    buffer += socket->readAll();
    while (true)
    {
        int pos = buffer.indexOf("\r\n");
        if (pos < 0) return;
        QByteArray line = buffer.left(pos);
        buffer = buffer.mid(pos + 2);
//        qDebug("QxtPop3Private::socketRead: received %s", line.data());
        switch (state)
        {
        case StartState: // we expect a greetings line, beginning with "+OK"
            if (!QxtPop3ReplyImpl::isAnswerOK(line))
            {
                qxt_p().disconnectFromHost();
            }
            state = Ready;
            {
                QxtPop3AuthReply* authReply = new QxtPop3AuthReply(this, 200000, this);
                pending.enqueue(authReply);
            }
            dequeue();
            break;
        case Busy: // a command is currently executed. Transmit the server response to the command, and if needed send the next line to the server
            if (current != 0)
            {
                QByteArray next = current->dialog(line);
                if (next.length() > 0)
                {
                    socket->write(next);
                }
            }
            break;
        default:
            break;
        }
    }
}

void QxtPop3Private::encrypted()
{
    if (state == Busy && current != 0) // startTLS emited during auth command
    {
        QByteArray next = current->dialog("");
        if (next.length() > 0)
        {
            socket->write(next);
        }
    }
}

void QxtPop3Private::authenticated()
{
    emit qxt_p().authenticated();
}

void QxtPop3Private::dequeue()
{
    if (state != Ready)
    {
        return;
    }
    if (pending.length() > 0)
    {
        current = pending.dequeue();
        connect(current, SIGNAL(finished(int)), this, SLOT(terminate(int)));
        current->qxt_d().status = QxtPop3Reply::Running;
        state = Busy;
        QByteArray cmdLine = current->dialog("");
        socket->write(cmdLine);
    }
}

void QxtPop3Private::terminate(int code)
{
    Q_UNUSED(code)
    state = Ready;
    current = 0;
    dequeue();
}
