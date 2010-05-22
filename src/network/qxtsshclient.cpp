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

#include "qxtsshchannel_p.h"
#include "qxtsshprocess.h"
#include "qxtsshtcpsocket.h"
#include <QTimer>


QxtSshClient::QxtSshClient(QObject * parent)
    :QObject(parent)
    ,d(new QxtSshClientPrivate){
    d->p=this;
}
QxtSshClient::~QxtSshClient(){
}

void QxtSshClient::connectToHost(QString user,QString host,int port){
    d->d_hostName=host;
    d->d_userName=user;
    d->d_port=port;
    d->d_state=1;
    d->connectToHost(host,port);
}

void QxtSshClient::disconnectFromHost (){
    d->d_reset();
}

void QxtSshClient::setPassphrase(QString pass){
    //if(d->d_passphrase!=pass){
        d->d_failedMethods.removeAll(QxtSshClient::PasswordAuthentication);
        d->d_failedMethods.removeAll(QxtSshClient::PublicKeyAuthentication);
        d->d_passphrase=pass;
        if(d->d_state>1){
            QTimer::singleShot(0,d,SLOT(d_readyRead()));
        }
        //}
}

void QxtSshClient::setKeyFiles(QString publicKey,QString privateKey){
    //if(d->d_publicKey!=publicKey ||  d->d_privateKey!=privateKey){
        d->d_failedMethods.removeAll(QxtSshClient::PublicKeyAuthentication);
        d->d_publicKey=publicKey;
        d->d_privateKey=privateKey;
        if(d->d_state>1){
            QTimer::singleShot(0,d,SLOT(d_readyRead()));
        }
        //}
}

bool QxtSshClient::loadKnownHosts(QString file,KnownHostsFormat c){
    Q_UNUSED(c);
    return (libssh2_knownhost_readfile(d->d_knownHosts, qPrintable(file),
                                      LIBSSH2_KNOWNHOST_FILE_OPENSSH)==0);
}
bool QxtSshClient::saveKnownHosts(QString file,KnownHostsFormat c) const{
    Q_UNUSED(c);
    return (libssh2_knownhost_writefile(d->d_knownHosts, qPrintable(file),
                                LIBSSH2_KNOWNHOST_FILE_OPENSSH)==0);
}

bool QxtSshClient::addKnownHost(QString hostname,QxtSshKey key){
    int typemask=LIBSSH2_KNOWNHOST_TYPE_PLAIN | LIBSSH2_KNOWNHOST_KEYENC_RAW;
    switch (key.type){
        case QxtSshKey::Dss:
            typemask|=LIBSSH2_KNOWNHOST_KEY_SSHDSS;
            break;
        case QxtSshKey::Rsa:
            typemask|=LIBSSH2_KNOWNHOST_KEY_SSHRSA;
            break;
        case QxtSshKey::UnknownType:
            return false;
    };


    return(libssh2_knownhost_add(d->d_knownHosts, qPrintable(hostname),
                                 NULL, key.key.data(), key.key.size(),
                                 typemask,  NULL));

}

QxtSshKey QxtSshClient::hostKey() const{
    return d->d_hostKey;
}
QString   QxtSshClient::hostName() const{
    return d->d_hostName;
}

QxtSshProcess * QxtSshClient::openProcessChannel(){
    if(d->d_state!=6){
        qWarning("cannot open channel before connected()");
        return NULL;
    }
    QxtSshProcess * s=new QxtSshProcess(this);
    d->d_channels.append(s);
    connect(s,SIGNAL(destroyed()),d,SLOT(d_channelDestroyed()));
    return s;
}

QxtSshTcpSocket * QxtSshClient::openTcpSocket(QString hostName,quint16 port){
    if(d->d_state!=6){
        qWarning("cannot open channel before connected()");
        return NULL;
    }
    QxtSshTcpSocket * s=new QxtSshTcpSocket(this);
    d->d_channels.append(s);
    connect(s,SIGNAL(destroyed()),d,SLOT(d_channelDestroyed()));
    s->d->openTcpSocket(hostName,port);
    return s;
}


static ssize_t qxt_p_libssh_recv(int socket,void *buffer, size_t length,int flags, void **abstract){
    Q_UNUSED(socket);
    Q_UNUSED(flags);
    QTcpSocket* c=reinterpret_cast<QTcpSocket*>(*abstract);
    int r=c->read(reinterpret_cast<char*>(buffer),length);
    if(r==0)
        return -EAGAIN;
    return r;
}

static ssize_t qxt_p_libssh_send(int socket,const void *buffer, size_t length,int flags, void **abstract){
    Q_UNUSED(socket);
    Q_UNUSED(flags);
    QTcpSocket* c=reinterpret_cast<QTcpSocket*>(*abstract);
    int r=c->write(reinterpret_cast<const char*>(buffer),length);
    if(r==0)
        return -EAGAIN;
    return r;
}





QxtSshClientPrivate::QxtSshClientPrivate()
    :d_session(0)
    ,d_knownHosts(0)
    ,d_state(0)
    ,d_errorCode(0)
{
    connect(this,SIGNAL(connected()),this,SLOT(d_connected()));
    connect(this,SIGNAL(disconnected()),this,SLOT(d_disconnected()));
    connect(this,SIGNAL(readyRead()),this,SLOT(d_readyRead()));

    Q_ASSERT(libssh2_init (0)==0);

    d_reset();

}

QxtSshClientPrivate::~QxtSshClientPrivate(){
    d_reset();
    if(d_session){
        libssh2_knownhost_free(d_knownHosts);
        libssh2_session_free(d_session);
    }
}

void QxtSshClientPrivate::d_connected(){
    d_state=2;
    d_readyRead();
}

void QxtSshClientPrivate::d_readyRead(){
    if(d_state==2){
        int sock=socketDescriptor();
        int ret=0;

        //1) initalise ssh session. exchange banner and stuff.

        if((ret = libssh2_session_startup(d_session, sock)) ==LIBSSH2_ERROR_EAGAIN){
            return;
        }
        if (ret) {
            qWarning("Failure establishing SSH session: %d", ret);
            emit p->error(QxtSshClient::UnexpectedShutdownError);
            d_reset();
            return;
        }


        //2) make sure remote is safe.
        size_t len;
        int type;
        const char * fingerprint = libssh2_session_hostkey(d_session, &len, &type);
        d_hostKey.key=QByteArray(fingerprint,len);
        d_hostKey.hash=QByteArray(libssh2_hostkey_hash(d_session,LIBSSH2_HOSTKEY_HASH_MD5),16);
        switch (type){
            case LIBSSH2_HOSTKEY_TYPE_RSA:
                d_hostKey.type=QxtSshKey::Rsa;
                break;
            case LIBSSH2_HOSTKEY_TYPE_DSS:
                d_hostKey.type=QxtSshKey::Dss;
                break;
            default:
                d_hostKey.type=QxtSshKey::UnknownType;
        }
        if(fingerprint) {
            struct libssh2_knownhost *host;
            int check = libssh2_knownhost_check(d_knownHosts, qPrintable(d_hostName),
                                                (char *)fingerprint, len,
                                                LIBSSH2_KNOWNHOST_TYPE_PLAIN|
                                                LIBSSH2_KNOWNHOST_KEYENC_RAW,
                                                &host);

            switch(check){
                case LIBSSH2_KNOWNHOST_CHECK_MATCH:
                    d_state=3;
                    d_readyRead();
                    return;
                case LIBSSH2_KNOWNHOST_CHECK_FAILURE:
                    d_delaydError=QxtSshClient::HostKeyInvalidError;
                    break;
                case LIBSSH2_KNOWNHOST_CHECK_MISMATCH:
                    d_delaydError=QxtSshClient::HostKeyMismatchError;
                    break;
                case LIBSSH2_KNOWNHOST_CHECK_NOTFOUND:
                    d_delaydError=QxtSshClient::HostKeyUnknownError;
                    break;
            }
        }else{
            d_delaydError=QxtSshClient::HostKeyInvalidError;
        }
        d_getLastError();
        d_reset();
        disconnectFromHost ();
        QTimer::singleShot(0,this,SLOT(d_delaydErrorEmit()));
        return;

    }else if(d_state==3){
        //3) try auth type "none" and get a list of other methods
        //   in the likely case that the server doesnt like "none"

        QByteArray username=d_userName.toLocal8Bit();
        char * alist=libssh2_userauth_list(d_session, username.data(),username.length());
        if(alist==NULL){
            if(libssh2_userauth_authenticated(d_session)){
                //null auth ok
                emit p->connected();
                d_state=5;
                return;
            }else if(libssh2_session_last_error(d_session,NULL,NULL,0)==LIBSSH2_ERROR_EAGAIN) {
                return;
            }else{
                d_getLastError();
                emit p->error(QxtSshClient::UnexpectedShutdownError);
                d_reset();
                emit p->disconnected();
                return;
            }
        }

        foreach(QByteArray m,QByteArray(alist).split(',')){
            if(m=="publickey"){
                d_availableMethods<<QxtSshClient::PublicKeyAuthentication;
            }
            else if(m=="password"){
                d_availableMethods<<QxtSshClient::PasswordAuthentication;
            }
        }
        d_state=4;
        d_readyRead();
    }else if(d_state==4){
        qDebug("looking for auth option");
        if(d_availableMethods.contains(QxtSshClient::PublicKeyAuthentication) &&
           !d_privateKey.isNull() &&
           !d_failedMethods.contains(QxtSshClient::PublicKeyAuthentication)){

            d_currentAuthTry=QxtSshClient::PublicKeyAuthentication;
            d_state=5;
            d_readyRead();
            return;
        }
        if(d_availableMethods.contains(QxtSshClient::PasswordAuthentication) &&
           !d_passphrase.isNull() &&
           !d_failedMethods.contains(QxtSshClient::PasswordAuthentication)){

            d_currentAuthTry=QxtSshClient::PasswordAuthentication;
            d_state=5;
            d_readyRead();
            return;
        }
        emit p->authenticationRequired(d_availableMethods);
    }else if(d_state==5){
        int ret;
        qDebug()<<"trying"<<d_currentAuthTry;
        if(d_currentAuthTry==QxtSshClient::PasswordAuthentication){
            ret=libssh2_userauth_password(d_session, qPrintable(d_userName),
                                          qPrintable(d_passphrase));

        }else if(d_currentAuthTry==QxtSshClient::PublicKeyAuthentication){
            ret=libssh2_userauth_publickey_fromfile(d_session,
                                                       qPrintable(d_userName),
                                                       qPrintable(d_publicKey),
                                                       qPrintable(d_privateKey),
                                                       qPrintable(d_passphrase));
        }
        if(ret==LIBSSH2_ERROR_EAGAIN ){
            return;
        }else if(ret==0){
            d_state=6;
            emit p->connected();
        }else{
            d_getLastError();
            emit p->error(QxtSshClient::AuthenticationError);
            d_failedMethods.append(d_currentAuthTry);
            d_state=4;
            d_readyRead();
        }
    }else if(d_state==6){
        QList<QxtSshChannel*>::const_iterator i;
        for (i = d_channels.constBegin(); i != d_channels.constEnd(); ++i){
            bool ret=(*i)->d->activate();
            if(!ret){
                d_getLastError();
            }
        }
    }else{
        qDebug("did not expect to receive data in this state");
    }
}

void QxtSshClientPrivate::d_reset(){
    qDebug("reset");

    //teardown
    if(d_knownHosts){
        libssh2_knownhost_free(d_knownHosts);
    }
    if(d_state>1){
        libssh2_session_disconnect(d_session,"good bye!");
    }
    if(d_session){
        libssh2_session_free(d_session);
    }

    d_state=0;
    d_errorCode=0;
    d_errorMessage=QString();
    d_failedMethods.clear();
    d_availableMethods.clear();


    //buildup
    d_session=libssh2_session_init_ex(NULL,NULL,NULL,reinterpret_cast<void*>(this));
    libssh2_session_callback_set(d_session,LIBSSH2_CALLBACK_RECV,reinterpret_cast<void*>(&qxt_p_libssh_recv));
    libssh2_session_callback_set(d_session,LIBSSH2_CALLBACK_SEND,reinterpret_cast<void*>(&qxt_p_libssh_send));
    Q_ASSERT(d_session);

    d_knownHosts= libssh2_knownhost_init(d_session);
    Q_ASSERT(d_knownHosts);

    libssh2_session_set_blocking(d_session,0);


}

void QxtSshClientPrivate::d_disconnected (){
    if(d_state!=0){
        qWarning("unexpected shutdown");
        d_reset();
    }
}

void QxtSshClientPrivate::d_getLastError(){
    char * msg;
    int len=0;
    d_errorCode=libssh2_session_last_error(d_session, &msg, &len,0);
    d_errorMessage=QString::fromLocal8Bit(QByteArray::fromRawData(msg,len));
}



void QxtSshClientPrivate::d_channelDestroyed(){
    QxtSshChannel* channel=  qobject_cast<QxtSshChannel*>(sender());
    d_channels.removeAll(channel);
}

void QxtSshClientPrivate::d_delaydErrorEmit(){
    emit p->error(d_delaydError);
}

