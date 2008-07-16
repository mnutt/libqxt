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

#include "qxtlinesocket_p.h"


#include <QIODevice>

/**
\class QxtLineSocket QxtLineSocket

\ingroup QxtCore

\brief Acts on a QIOdevice as baseclass for line-based protocols
*/






QxtLineSocket::QxtLineSocket (QIODevice * socket,QObject * parent):QObject(parent)
{
    QXT_INIT_PRIVATE(QxtLineSocket);
    qxt_d().socket=socket;
    connect(qxt_d().socket,SIGNAL(readyRead()),&qxt_d(),SLOT(readyRead()));
}

QxtLineSocket::QxtLineSocket (QObject * parent):QObject(parent)
{
    QXT_INIT_PRIVATE(QxtLineSocket);
    qxt_d().socket=0;
}

void QxtLineSocket::setSocket(QIODevice * a)
{
    if (qxt_d().socket)
        disconnect(qxt_d().socket);
    qxt_d().socket=a;
    connect(qxt_d().socket,SIGNAL(readyRead()),&qxt_d(),SLOT(readyRead()));
}




QIODevice * QxtLineSocket::socket() const
{
    return qxt_d().socket;
}


void QxtLineSocket::sendLine(QByteArray a)
{
    qxt_d().socket->write(a.replace('\n',"")+'\n');
}

void QxtLineSocket::newLine(QByteArray a)
{
    emit(newLineReceived(a));
}


void QxtLineSocketPrivate::readyRead()
{
    rbuff+=socket->readAll();

    int i=0;
    while((i=rbuff.indexOf('\n'))>-1)
    {
        (&qxt_p())->newLine(rbuff.left(i));
        rbuff=rbuff.mid(i+1);
    }
}





