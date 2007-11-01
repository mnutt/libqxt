/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtNetwork module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
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
    connect(socket,SIGNAL(readyRead()),&qxt_d(),SLOT(readyRead()));
}

QIODevice * QxtLineSocket::socket()
{
    return qxt_d().socket;
}

void QxtLineSocket::newLine(QByteArray a)
{
    emit(newLineReceived(a));
}


void QxtLineSocketPrivate::readyRead()
{
    rbuff+=socket->readAll();

    int i=rbuff.indexOf('\n');
    if (i>-1)
    {
        (&qxt_p())->newLine(rbuff.left(i));
        rbuff=rbuff.mid(i+1);
    }
}



