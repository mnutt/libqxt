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

#ifndef QXT_SSH_CLIENT_H
#define QXT_SSH_CLIENT_H

#include <QObject>
#include <QList>
#include "qxtglobal.h"

class QXT_NETWORK_EXPORT QxtSshKey{
 public:
    enum Type{
        UnknownType,
        Rsa,
        Dss
    };
    QByteArray hash;
    QByteArray key;
    Type type;
};


class QxtSshProcess;
class QxtSshTcpSocket;
class QxtSshClientPrivate;
class QXT_NETWORK_EXPORT QxtSshClient : public QObject{
    Q_OBJECT
public:
    enum AuthenticationMethod{
        PasswordAuthentication,
        PublicKeyAuthentication
    };
    enum KnownHostsFormat{
        OpenSslFormat
    };
    enum Error{
        AuthenticationError,
        HostKeyUnknownError,
        HostKeyInvalidError,
        HostKeyMismatchError,
        ConnectionRefusedError,
        UnexpectedShutdownError,
        HostNotFoundError,
        SocketError,
        UnknownError
    };

    QxtSshClient(QObject * parent=0);
    ~QxtSshClient();

    void connectToHost(const QString & username,const QString & hostname,int port = 22);
    void disconnectFromHost ();
    void setPassphrase(const QString & pass);
    void setKeyFiles(const QString & publicKey,const QString & privateKey);

    bool loadKnownHosts(const QString & file,KnownHostsFormat c = OpenSslFormat);
    bool saveKnownHosts(const QString & file,KnownHostsFormat c = OpenSslFormat) const;
    bool addKnownHost(const QString & hostname,const QxtSshKey & key);

    QxtSshKey hostKey() const;
    QString   hostName() const;

    QxtSshProcess * openProcessChannel();
    QxtSshTcpSocket * openTcpSocket(const QString & hostName,quint16 port);
signals:
    void connected();
    void disconnected();
    void error (QxtSshClient::Error error);
    void authenticationRequired(QList<QxtSshClient::AuthenticationMethod> availableMethods);
private:
    QxtSshClientPrivate * d;
    friend class QxtSshClientPrivate;
    friend class QxtSshChannelPrivate;
};

#include <QDebug>
inline QDebug operator<< (QDebug d, const QxtSshClient::AuthenticationMethod  & m){
    switch(m){
        case QxtSshClient::PasswordAuthentication:
            d<<"QxtSshClient::PasswordAuthentication";
            break;
        case QxtSshClient::PublicKeyAuthentication:
            d<<"QxtSshClient::PublicKeyAuthentication";
            break;
    }
    return d;
}
inline QDebug operator<< (QDebug d, const QxtSshKey::Type  & m){
    switch(m){
        case QxtSshKey::Dss:
            d<<"QxtSshKey::Dss";
            break;
        case QxtSshKey::Rsa:
            d<<"QxtSshKey::Rsa";
            break;
        case QxtSshKey::UnknownType:
            d<<"QxtSshKey::UnknownType";
            break;
    }
    return d;
}



#endif
