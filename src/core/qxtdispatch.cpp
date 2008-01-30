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
#include "qxtdispatch.h"

/**
\class QxtDispatch QxtDispatch

\ingroup QxtCore

\brief connect multiple QIODevice to one

\sa QIODevice

*/

/**
\fn QxtDispatch::QxtDispatch(QObject * parent)
\brief creates a new QxtDispatch


\fn void QxtDispatch::addInput       (QIODevice *)
\brief adds the device to the input list.
when the device emits readyRead, QxtDispatch will read all data from it and emit readyRead itself.


\fn void QxtDispatch::removeInput    (QIODevice *)
\brief removes the device from the input list


\fn void QxtDispatch::addOutput      (QIODevice *)
\brief adds the device to the output list.
when you write to the QxtDispatch, it will dispatch the data to all output devices

\fn void QxtDispatch::removeOutput   (QIODevice *)
\brief removes the device from the output list


\fn bool QxtDispatch::isSequential() const
\reimp


\fn qint64 QxtDispatch::bytesAvailable() const
\reimp


\fn qint64 QxtDispatch::readData ( char * data, qint64 maxSize )
\reimp


\fn qint64 QxtDispatch::writeData ( const char * data, qint64 maxSize )
\reimp

*/



QxtDispatch::QxtDispatch(QObject * parent):QIODevice(parent)
{
    setOpenMode (QIODevice::ReadWrite);
}

void QxtDispatch::addInput       (QIODevice * d)
{
    connect (d,SIGNAL(destroyed ( QObject *)),this,SLOT(extDestroyed(QObject *)));
    connect (d,SIGNAL(readyRead()),this,SLOT(extReadyRead()));

}

void QxtDispatch::removeInput    (QIODevice * d)
{
    disconnect (d,SIGNAL(readyRead()),this,SLOT(extReadyRead()));
}

void QxtDispatch::addOutput      (QIODevice * device)
{
    Q_ASSERT_X(device!=this,Q_FUNC_INFO,"you can't QxtYDevice as its own output");
    connect (device,SIGNAL(destroyed ( QObject *)),this,SLOT(extDestroyed(QObject *)));
    outputs<<device;
}

void QxtDispatch::removeOutput   (QIODevice * d)
{
    outputs.removeAll(d);
}

void QxtDispatch::extReadyRead()
{
    QByteArray d=static_cast<QIODevice*>(sender())->readAll();
    char * data=d.data();
    for(int i=0;i<d.size();i++)
        q.enqueue(*data++);
    emit readyRead();
}
void QxtDispatch::extDestroyed(QObject *o)
{
    removeOutput(static_cast<QxtYDevice*>(o));
    removeInput(static_cast<QxtYDevice*>(o));
}


bool QxtDispatch::isSequential() const
{
    return true; //maybe?
}


qint64 QxtDispatch::bytesAvailable () const
{
    return q.count();
}


qint64 QxtDispatch::readData ( char * data, qint64 maxSize )
{
    qint64 i=0;
    for (;i<maxSize;i++)
    {
        if (q.isEmpty())
            break;
        (*data++)=q.dequeue();
    }
    return i;
}

qint64 QxtDispatch::writeData ( const char * data, qint64 maxSize )
{
    foreach(QIODevice *d,outputs)
        d->write(data,maxSize);
    return maxSize;
}
