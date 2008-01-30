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
#include "qxtydevice.h"

/**
\class QxtYDevice QxtYDevice

\ingroup QxtCore

\brief make one QIODevice out of two by putting one in the read and the other in the write channel

\sa QIODevice

*/

/**
\fn QxtYDevice::QxtYDevice(QObject * parent)
\brief creates a QxtYDevice




\fn void setWriteDevice(QIODevice*)
\brief set the device to delegate write operations to


\fn void setReadDevice(QIODevice*)
\brief set the device to read from


\fn bool QxtYDevice::isSequential() const
\reimp


\fn qint64 QxtYDevice::bytesAvailable() const
\reimp


\fn qint64 QxtYDevice::readData ( char * data, qint64 maxSize )
\reimp


\fn qint64 QxtYDevice::writeData ( const char * data, qint64 maxSize )
\reimp

*/



QxtYDevice::QxtYDevice(QObject * parent):QIODevice(parent)
{
    setOpenMode (QIODevice::ReadWrite); //we don't know the real state
    m_w=0;
    m_r=0;
}


void QxtYDevice::setWriteDevice(QIODevice* i)
{
    m_w=i;
}
void QxtYDevice::setReadDevice(QIODevice* i)
{
    m_r=i;
    connect(i,SIGNAL(readyRead()),this,SIGNAL(readyRead()));
}


bool QxtYDevice::isSequential() const
{
    return true;//for now
}


qint64 QxtYDevice::bytesAvailable () const
{
    return m_r->bytesAvailable();
}


qint64 QxtYDevice::readData ( char * data, qint64 maxSize )
{
    return m_r->read(data,maxSize);
}

qint64 QxtYDevice::writeData ( const char * data, qint64 maxSize )
{
    return m_w->write(data,maxSize);
}



