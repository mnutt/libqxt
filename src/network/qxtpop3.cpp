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
  one gets a pointer to a QxtPop3Command, that can be used to get feedback
  (typically connect its completed() signal to some slot handling the result).
 */

#include "qxtpop3.h"
#include "qxtpop3_p.h"
#include "qxtpop3command_p.h"

#include <QTcpSocket>
#include <QNetworkInterface>
#ifndef QT_NO_OPENSSL
#    include <QSslSocket>
#endif




class QxtPop3AuthCmd: public QxtPop3Command
{
public:
    QxtPop3AuthCmd(QxtPop3Private* pop,
                   int timeout);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        STLSSent,
        TLSOK,
        UserSent,
        PassSent,
    };

private:
    QxtPop3Private* pop;
    bool startTLSdisabled;
    State state;

};

QxtPop3AuthCmd::QxtPop3AuthCmd(QxtPop3Private* pop,
                               int timeout) : QxtPop3Command(timeout, pop), pop(pop)/*, username(username), password(password), startTLSdisabled(startTLSdisabled)*/
{
    state = StartState;
    startTLSdisabled = pop->disableStartTLS;
}

QByteArray QxtPop3AuthCmd::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
#ifndef QT_NO_OPENSSL
        if (!startTLSdisabled)
        {
            ret = QxtPop3CommandPrivate::buildCmd("STLS", "");
            state = STLSSent;
            break;
        }
    case TLSOK:   // fallthrough
#endif
        ret = QxtPop3CommandPrivate::buildCmd("USER", pop->username);
        state = UserSent;
        break;
#ifndef QT_NO_OPENSSL
    case STLSSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            pop->socket->startClientEncryption();
            state = TLSOK;
        }
        else
        {
            qWarning("startTLS doesn't seem to be supported");
            emit completed(Failed);
            pop->socket->disconnectFromHost();
        }
        break;
#endif
    case UserSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            ret = QxtPop3CommandPrivate::buildCmd("PASS", pop->password);
            state = PassSent;
        }
        break;
    case PassSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            // authenticated
            emit completed(OK);
        }
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3QuitCmd: public QxtPop3Command
{
public:
    QxtPop3QuitCmd(int timeout, QObject* parent = 0);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        QuitSent
    };
private:
    State state;
};

QxtPop3QuitCmd::QxtPop3QuitCmd(int timeout, QObject* parent) : QxtPop3Command(timeout, parent)
{
    state = StartState;
}

QByteArray QxtPop3QuitCmd::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = QxtPop3CommandPrivate::buildCmd("QUIT", "");
        state = QuitSent;
        break;
    case QuitSent:
        emit completed(OK);
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3StatCmd: public QxtPop3Command
{
public:
    QxtPop3StatCmd(int& count, int& size, int timeout, QObject* parent = 0);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        StatSent
    };

private:
    State state;
    int& m_count;
    int& m_size;
};

QxtPop3StatCmd::QxtPop3StatCmd(int& count, int& size, int timeout, QObject* parent): QxtPop3Command(timeout, parent), m_count(count), m_size(size)
{
    state = StartState;
}

QByteArray QxtPop3StatCmd::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = QxtPop3CommandPrivate::buildCmd("STAT", "");
        state = StatSent;
        break;
    case StatSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            QTextStream input(received);
            QString ok;
            input >> ok >> m_count >> m_size;
            emit completed(OK);
        } else {
            setStatus(Error);
            setError(received);
            emit completed(Failed);
        }
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3ListCmd: public QxtPop3Command
{
public:
    QxtPop3ListCmd(QList<QPair<int,int> >& list, int timeout, QObject* parent = 0);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        ListSent,
        OKReceived
    };

private:
    State state;
    QList<QPair<int,int> >& m_list;
};

QxtPop3ListCmd::QxtPop3ListCmd(QList<QPair<int,int> >& list, int timeout, QObject* parent): QxtPop3Command(timeout, parent), m_list(list)
{
    state = StartState;
}

QByteArray QxtPop3ListCmd::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = QxtPop3CommandPrivate::buildCmd("LIST", "");
        state = ListSent;
        break;
    case ListSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            state = OKReceived;
        } else {
            setStatus(Error);
            setError(received);
            emit completed(Failed);
        }
        break;
    case OKReceived:
        {
            QStringList words = QString(received).split(" ");
            if (words[0] == ".")
            {
                emit completed(OK);
            }
            else
            {
                QPair<int,int> pair(words[0].toInt(), words[1].toInt());
                m_list.append(pair);
            }
        }
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3RetrCmd: public QxtPop3Command
{
public:
    QxtPop3RetrCmd(int which, QxtMailMessage*& msg, int timeout, QObject* parent=0);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        ListSent,
        RetrSent,
        OKReceived
    };

private:
    State state;
    QByteArray message;
    QxtMailMessage*& m_msg;
    int m_which;
    int m_length;
};

QxtPop3RetrCmd::QxtPop3RetrCmd(int which, QxtMailMessage*& msg, int timeout, QObject* parent): QxtPop3Command(timeout, parent), m_msg(msg), m_which(which), m_length(0)
{
    state = StartState;
}

QByteArray QxtPop3RetrCmd::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = QxtPop3CommandPrivate::buildCmd("LIST", QByteArray().number(m_which));
        state = ListSent;
        break;
    case ListSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            m_length = received.split(' ').at(2).toInt();
            ret = QxtPop3CommandPrivate::buildCmd("RETR", QByteArray().number(m_which));
            state = RetrSent;
        } else {
            setStatus(Error);
            setError(received);
            emit completed(Failed);
        }
        break;
    case RetrSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            state = OKReceived;
        } else {
            setStatus(Error);
            setError(received);
            emit completed(Failed);
        }
        break;
    case OKReceived:
        {
            if ((received.length() > 0) && (received[0] == '.'))
            {
                if (received.length() == 1)
                {
                    // Termination line. The whole message is received by now.
                    m_msg = new QxtMailMessage(message);
                    emit completed(OK);
                }
                else // remove first dot
                {
                    received = received.mid(1);
                }
            }
            message += received + "\r\n";
            int p = (100*message.length())/m_length;
            emit progress(p);
        }
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3DeleCmd: public QxtPop3Command
{
public:
    QxtPop3DeleCmd(int which, int timeout, QObject* parent=0);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        DeleSent
    };

private:
    State state;
    int m_which;
};

QxtPop3DeleCmd::QxtPop3DeleCmd(int which, int timeout, QObject* parent): QxtPop3Command(timeout, parent), state(StartState), m_which(which)
{
    // empty ctor
}



QByteArray QxtPop3DeleCmd::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = QxtPop3CommandPrivate::buildCmd("DELE", QByteArray().number(m_which));
        state = DeleSent;
        break;
    case DeleSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            emit completed(OK);
        } else {
            setStatus(Error);
            setError(received);
            emit completed(Failed);
        }
        break;
    default:
        break;
    }
    return ret;
}

class QxtPop3RsetCmd: public QxtPop3Command
{
public:
    QxtPop3RsetCmd(int timeout, QObject* parent=0);
    QByteArray dialog(QByteArray received);
    enum State {
        StartState,
        RsetSent
    };

private:
    State state;
};

QxtPop3RsetCmd::QxtPop3RsetCmd(int timeout, QObject* parent): QxtPop3Command(timeout, parent), state(StartState)
{
    // empty ctor
}



QByteArray QxtPop3RsetCmd::dialog(QByteArray received)
{
    QByteArray ret = "";
    switch (state)
    {
    case StartState:
        ret = QxtPop3CommandPrivate::buildCmd("RSET", "");
        state = RsetSent;
        break;
    case RsetSent:
        if (QxtPop3CommandPrivate::isAnswerOK(received))
        {
            emit completed(OK);
        } else {
            setStatus(Error);
            setError(received);
            emit completed(Failed);
        }
        break;
    default:
        break;
    }
    return ret;
}

QxtPop3Private::QxtPop3Private() : QObject(0)
{
    // empty ctor
}

/*!

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

 */
QByteArray QxtPop3::username() const
{
    return qxt_d().username;
}

void QxtPop3::setUsername(const QByteArray& username)
{
    qxt_d().username = username;
}

QByteArray QxtPop3::password() const
{
    return qxt_d().password;
}

void QxtPop3::setPassword(const QByteArray& password)
{
    qxt_d().password = password;
}

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
  Close the connection.
 */
void QxtPop3::disconnectFromHost()
{
    socket()->disconnectFromHost();
}

bool QxtPop3::startTlsDisabled() const
{
    return qxt_d().disableStartTLS;
}

void QxtPop3::setStartTlsDisabled(bool disable)
{
    qxt_d().disableStartTLS = disable;
}

#ifndef QT_NO_OPENSSL
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

bool QxtPop3::isConnected() const
{
    return qxt_d().state != QxtPop3Private::Disconnected;
}

/*!
   Implement the STAT POP3 command.
   When the command is completed, \a count contains the message count on the server mailbox,
   and \a size contains the total size in bytes stored on the server mailbox.
 */
QxtPop3Command* QxtPop3::stat(int &count, int &size, int timeout)
{
    QxtPop3StatCmd* cmd = new QxtPop3StatCmd(count, size, timeout, this);
    qxt_d().pending.enqueue(cmd);
    qxt_d().dequeue();
    return cmd;
}

/*!
   Implement the LIST POP3 command.
   When the command is completed, \a list contains a list of pairs, the first member of each being the message number,
   the second being the message size in bytes.
 */
QxtPop3Command* QxtPop3::messageList(QList<QPair<int,int> >& list, int timeout)
{
    QxtPop3ListCmd* cmd = new QxtPop3ListCmd(list, timeout, this);
    qxt_d().pending.enqueue(cmd);
    qxt_d().dequeue();
    return cmd;
}

/*!
   Retrieve message nb \a which.
   When the command is completed, \a message points to the retrieved message.
   The user owns the message and should delete it after use.
 */
QxtPop3Command* QxtPop3::retrieveMessage(int which, QxtMailMessage*& message, int timeout)
{
    QxtPop3RetrCmd* cmd = new QxtPop3RetrCmd(which, message, timeout, this);
    qxt_d().pending.enqueue(cmd);
    qxt_d().dequeue();
    return cmd;
}

//QxtPop3Command* QxtPop3::retrieveAll(QList<QxtMailMessage>& list, int timeout)
//{
//
//}

/*!
   Delete the message nb \a which.
   Until the session is closed, the message can be undeleted by a reset.
 */
QxtPop3Command* QxtPop3::deleteMessage(int which, int timeout)
{
    QxtPop3DeleCmd* cmd = new QxtPop3DeleCmd(which, timeout, this);
    qxt_d().pending.enqueue(cmd);
    qxt_d().dequeue();
    return cmd;
}

//QxtPop3Command* QxtPop3::deleteAll(int timeout)
//{
//
//}

/*!
  Reset the session. All messages marked as deleted are undeleted.
 */
QxtPop3Command* QxtPop3::reset(int timeout)
{
    QxtPop3RsetCmd* cmd = new QxtPop3RsetCmd(timeout, this);
    qxt_d().pending.enqueue(cmd);
    qxt_d().dequeue();
    return cmd;
}

//QxtPop3Command* QxtPop3::top(int which, int lines, QStringList*& top, int timeout)
//{
//
//}

/*!
  Close the session, and disconnect from the server.
 */
QxtPop3Command* QxtPop3::quit(int timeout)
{
    QxtPop3QuitCmd* cmd = new QxtPop3QuitCmd(timeout, this);
    qxt_d().pending.enqueue(cmd);
    qxt_d().dequeue();
    return cmd;
}


void QxtPop3Private::socketError(QAbstractSocket::SocketError err)
{
    if (err == QAbstractSocket::SslHandshakeFailedError)
    {
        emit qxt_p().encryptionFailed();
        emit qxt_p().encryptionFailed( socket->errorString().toAscii() );
        if (current != 0) current->cancel();
    }
    else if (state == StartState)
    {
        emit qxt_p().connectionFailed();
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
            if (!QxtPop3CommandPrivate::isAnswerOK(line))
            {
                qxt_p().disconnectFromHost();
            }
            state = Ready;
            {
                QxtPop3AuthCmd* authCmd = new QxtPop3AuthCmd(this, 200000);
                pending.enqueue(authCmd);
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

void QxtPop3Private::dequeue()
{
    if (state != Ready)
    {
        return;
    }
    if (pending.length() > 0)
    {
        current = pending.dequeue();
        connect(current, SIGNAL(completed(int)), this, SLOT(terminate(int)));
        current->qxt_d().status = QxtPop3Command::Running;
        state = Busy;
        QByteArray cmdLine = current->dialog("");
        socket->write(cmdLine);
    }
}

void QxtPop3Private::terminate(int code)
{
    state = Ready;
    current = 0;
    dequeue();
}
#endif // QT_NO_OPENSSL
