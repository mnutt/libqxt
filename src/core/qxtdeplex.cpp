/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
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
#include "qxtdeplex_p.h"

/**
\class QxtDeplex QxtDeplex

\ingroup QxtCore

\brief put a standard QIODevice into a QxtPipe chain



implements a normal QxtPipe with the exception that r/w operations are delegated to the device set by setDevice()

\sa QIODevice
\sa QxtPipe
*/

/**
\fn QxtDeplex::QxtDeplex(QObject * parent)
\brief creates a new QxtDeplex


\fn QxtDeplex::QxtDeplex(QIODevice * device,QObject * parent)
\brief creates a new QxtDeplex and delegates r/w operations to the device


\fn void QxtDeplex::setDevice(QIODevice * device);
\brief delegate r/w operations to the device

\fn     QIODevice *QxtDeplex::device() const;
\brief returns the device currently delegated


\fn virtual void   QxtDeplex::receiveData (QByteArray data, const QxtPipe * sender )
\reimp

*/





QxtDeplex::QxtDeplex(QObject * parent):QxtPipe(parent)
{
    QXT_INIT_PRIVATE(QxtDeplex);
}
QxtDeplex::QxtDeplex(QIODevice * device,QObject * parent):QxtPipe(parent)
{
    QXT_INIT_PRIVATE(QxtDeplex);
    setDevice(device);
}

void QxtDeplex::setDevice(QIODevice * device)
{
    if(qxt_d().delegate)
    {
        QObject::disconnect(qxt_d().delegate,SIGNAL(readyRead()),&qxt_d(),SLOT(readyRead()));
        QObject::disconnect(qxt_d().delegate,SIGNAL(destroyed(QObject *)),&qxt_d(),SLOT(extDestroyed(QObject *)));
    }
    qxt_d().delegate=device;
    if(qxt_d().delegate)
    {
        QObject::connect(qxt_d().delegate,SIGNAL(readyRead()),&qxt_d(),SLOT(readyRead()));
        QObject::connect(qxt_d().delegate,SIGNAL(destroyed(QObject *)),&qxt_d(),SLOT(extDestroyed(QObject *)));
    }
}
QIODevice *QxtDeplex::device() const
{
    return qxt_d().delegate;
}

void QxtDeplexPrivate::readyRead()
{
    QByteArray d=static_cast<QIODevice*>(sender())->readAll();

    qxt_p().enqueData(d);
    qxt_p().sendData(d);
}

void QxtDeplexPrivate::extDestroyed(QObject *)
{
    delegate=0;
}


qint64 QxtDeplex::writeData ( const char * a, qint64 s )
{
    if(!qxt_d().delegate)
        return 0;
    return qxt_d().delegate->write(a,s);

}
void  QxtDeplex::receiveData (QByteArray data, const QxtPipe *  )
{
    if(!qxt_d().delegate)
        return;
    qxt_d().delegate->write(data);
}
