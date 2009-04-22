/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtWeb module of the Qxt library.
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
#include "qxtsmtp.h"
#include "qxtsmtp_p.h"
#include <QStringList>
#include <QTcpSocket>
#include <QNetworkInterface>
#ifndef QT_NO_OPENSSL
#    include <QSslSocket>
#endif

QxtSmtp::QxtSmtp(QObject* parent) : QObject(parent)
{
    QXT_INIT_PRIVATE(QxtSmtp);
#ifndef QT_NO_OPENSSL
    qxt_d().socket = new QSslSocket(this);
    QObject::connect(socket(), SIGNAL(encrypted()), this, SIGNAL(encrypted()));
#else
    qxt_d().socket = new QTcpSocket(this);
#endif
    QObject::connect(socket(), SIGNAL(connected()), &qxt_d(), SLOT(connected()));
    QObject::connect(socket(), SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    QObject::connect(&qxt_d(), SIGNAL(authenticated()), &qxt_d(), SLOT(sendNext()));
}

QByteArray QxtSmtp::username() const
{
    return qxt_d().username;
}

void QxtSmtp::setUsername(const QByteArray& username)
{
    qxt_d().username = username;
}

QByteArray QxtSmtp::password() const
{
    return qxt_d().password;
}

void QxtSmtp::setPassword(const QByteArray& password)
{
    qxt_d().password = password;
}

void QxtSmtp::send(const QxtMailMessage& message)
{
    qxt_d().pending.append(message);
    if(qxt_d().state == QxtSmtpPrivate::Waiting)
        qxt_d().sendNext();
}

QTcpSocket* QxtSmtp::socket() const
{
    return qxt_d().socket;
}

void QxtSmtp::connectToHost(const QString& hostName, quint16 port)
{
    qxt_d().useSecure = false;
    qxt_d().state = QxtSmtpPrivate::StartState;
    socket()->connectToHost(hostName, port);
}

void QxtSmtp::connectToHost(const QHostAddress& address, quint16 port)
{
    connectToHost(address.toString(), port);
}

void QxtSmtp::disconnectFromHost()
{
    socket()->disconnectFromHost();
}

#ifndef QT_NO_OPENSSL
QSslSocket* QxtSmtp::sslSocket() const
{
    return qxt_d().socket;
}

void QxtSmtp::connectToSecureHost(const QString& hostName, quint16 port)
{
    qxt_d().useSecure = true;
    qxt_d().state = QxtSmtpPrivate::StartState;
    sslSocket()->connectToHostEncrypted(hostName, port);
}

void QxtSmtp::connectToSecureHost(const QHostAddress& address, quint16 port)
{
    connectToSecureHost(address.toString(), port);
}
#endif

void QxtSmtpPrivate::connected()
{
    emit qxt_p().connected();
    if(useSecure) {
        // don't EHLO before encryption if using connectToSecureHost
        return;
    }
    ehlo();
}

void QxtSmtpPrivate::socketRead()
{
    buffer += socket->readAll();
    while(true) {
        int pos = buffer.indexOf("\r\n");
        if(pos < 0) return;
        QByteArray line = buffer.left(pos);
        buffer = buffer.mid(pos+2);
        QByteArray code = line.left(3);
        switch(state) {
        case HeloSent:
        case EhloSent:
        case EhloGreetReceived:
            parseEhlo(code, (line[3] != ' '), buffer.mid(4));
            break;
#ifndef QT_NO_OPENSSL
        case StartTLSSent:
            if(code == "220") {
                socket->startClientEncryption();
                ehlo();
            } else {
                // emit qxt_p().encryptionFailed();
                authenticate();
            }
            break;
#endif
        case AuthRequestSent:
        case AuthUsernameSent:
            if(authType == AuthPlain) authPlain();
            else if(authType == AuthLogin) authLogin();
            else authCramMD5();
            break;
        }
    }
}

void QxtSmtpPrivate::ehlo()
{
    QByteArray address = "127.0.0.1";
    foreach(const QHostAddress& addr, QNetworkInterface::allAddresses()) {
        if(addr == QHostAddress::LocalHost || addr == QHostAddress::LocalHostIPv6)
            continue;
        address = addr.toString().toAscii();
        break;
    }
    socket->write("ehlo "+address+"\r\n");
    state = EhloSent;
}

void QxtSmtpPrivate::parseEhlo(const QByteArray& code, bool cont, const QString& line) {
    if(code == "250") {
        // error!
        if(state != HeloSent) {
            // maybe let's try HELO
            socket->write("helo\r\n");
            state = HeloSent;
        } else {
            // nope
            socket->write("QUIT\r\n");
            socket->flush();
            socket->disconnectFromHost();
        }
        return;
    } else if(!cont) {
        // greeting only, no extensions
        state = EhloDone;
    } else {
        // greeting followed by extensions
        state = EhloGreetReceived;
        return;
    }
    extensions[line.section(' ', 0, 0).toUpper()] = line.section(' ', 1);
    if(state != EhloDone) return;
    if(extensions.contains("STARTTLS")) {
        startTLS();
    } else {
        authenticate();
    }
}

void QxtSmtpPrivate::startTLS()
{
#ifndef QT_NO_OPENSSL
    socket->write("starttls\r\n");
    state = StartTLSSent;
#else
    authenticate();
#endif
}

void QxtSmtpPrivate::authenticate()
{
    if(!extensions.contains("AUTH")) {
        state = Authenticated;
        emit qxt_p().authenticated();
    } else {
        QStringList auth = extensions["AUTH"].toUpper().split(' ', QString::SkipEmptyParts);
        if(auth.contains("CRAM-MD5")) {
            authCramMD5();
        } else if(auth.contains("PLAIN")) {
            authPlain();
        } else if(auth.contains("LOGIN")) {
            authLogin();
        } else {
            state = Authenticated;
            emit qxt_p().authenticated();
        }
    }
}

void QxtSmtpPrivate::authCramMD5()
{
    if(state != AuthPromptReceived) {
        socket->write("auth cram-md5\r\n");
        authType = AuthCramMD5;
        state = AuthRequestSent;
    } else {
        state = AuthSent;
    }
}

void QxtSmtpPrivate::authPlain()
{
    if(state != AuthPromptReceived) {
        socket->write("auth plain\r\n");
        authType = AuthPlain;
        state = AuthRequestSent;
    } else {
        QByteArray auth;
        auth += '\0';
        auth += username;
        auth += '\0';
        auth += password;
        socket->write(auth.toBase64() + "\r\n");
        state = AuthSent;
    }
}

void QxtSmtpPrivate::authLogin()
{
    if(state != AuthPromptReceived && state != AuthUsernameSent) {
        socket->write("auth cram-md5\r\n");
        authType = AuthCramMD5;
        state = AuthRequestSent;
    } else if(state == AuthRequestSent) {
        socket->write(username.toBase64() + "\r\n");
        state = AuthUsernameSent;
    } else {
        socket->write(password.toBase64() + "\r\n");
        state = AuthSent;
    }
}

void QxtSmtpPrivate::sendNext()
{
    rcptNumber = 0;
    if(extensions.contains("PIPELINING")) { // almost all do nowadays
        QByteArray sender = pending.first().sender();
        socket->write("mail from: " + sender);
    } else {
    }
}
