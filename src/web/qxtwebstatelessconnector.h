/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtWeb  module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
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
#ifndef QxtWebStatelessConnection_header_guards_oaksndoapsid
#define QxtWebStatelessConnection_header_guards_oaksndoapsid

#include <QHttpHeader>
#include <QHttpResponseHeader>
#include <QHttpRequestHeader>
#include <QAbstractSocket>

class QxtWebStatelessConnection  : public QIODevice
{
Q_OBJECT
public:
    virtual const   QHttpResponseHeader & response() const  =0;
    virtual         QHttpResponseHeader & response()        =0;

    virtual const   QHttpRequestHeader & request () const   =0;
    virtual         QHttpRequestHeader & request ()         =0;
protected:
    QxtWebStatelessConnection(QObject * parent=0):QIODevice(parent){}

};


class QxtWebStatelessConnector : public QObject
{
Q_OBJECT
public:
    virtual bool isMultiplexing()=0;
    virtual bool start (quint16 port,const QHostAddress & address)=0;
    virtual QAbstractSocket::SocketError serverError () const=0;



    virtual QxtWebStatelessConnection * nextPendingConnection ()=0;
    virtual bool hasPendingConnections () const =0;


    virtual bool waitForNewConnection ( int msec = 0, bool * timedOut = 0 )=0;

protected:
    QxtWebStatelessConnector(QObject * parent=0):QObject(parent){}

signals:
    void newConnection ();
};

#endif

