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

#include "qxtpipe.h"
#include <QList>
#include <QQueue>

/**
 * \class  QxtPipe QxtPipe
 * \ingroup QxtCore
 * \brief a pipeable QIODevice
 *
 * pipes can be connected to other pipes, to exchange data \n
 * The default implementation uses a buffer. \n
 * Reimplement to make your custom class able to be connected into a pipe chain. \n
 *
 * Example usage:
 * \code
 * QxtPipe p1;
 * QxtPipe p2;
 * p1|p2;
 * p1.write("hello world");
 * qDebug()<<p2.readAll();
 * \endcode
*/




class QxtPipePrivate:public QxtPrivate<QxtPipe>
{
    public:
        QQueue<char> q;
        QList<QxtPipe*> pipes;
};

/**
 * Contructs a new QxtPipe.
 */
QxtPipe::QxtPipe(QObject * parent):QIODevice(parent)
{
    setOpenMode (QIODevice::ReadWrite);
}


/** reimplemented from QIODevice*/
bool QxtPipe::isSequential () const
{
    return true;
}

/** reimplemented from QIODevice*/
qint64 QxtPipe::bytesAvailable () const
{
    return qxt_d().q.count();
}

/**
 * pipes the output of this instance to the \p other  QxtPipe
 */
bool QxtPipe::connect (QxtPipe & other )
{
    qxt_d().pipes.append(&other);
    return true;
}

/**
 * cuts the pipe to the \p other QxtPipe
 */
bool QxtPipe::disconnect (QxtPipe & other )
{
    qxt_d().pipes.removeAll(&other);
    return true;
}

/**
 * pipes the output of this instance to the \p other  QxtPipe
 * convinence function for QxtPipe::connect
 */
QxtPipe & QxtPipe::operator | ( QxtPipe & target)
{
    connect(target);
    return *this;
}

/** reimplemented from QIODevice*/
qint64 QxtPipe::readData ( char * data, qint64 maxSize )
{
    QQueue<char> * q=&qxt_d().q;

    qint64 i=0;
    for (;i<maxSize;i++)
    {
        if (q->isEmpty())
            break;
        (*data++)=q->dequeue();
    }
    return i;
}

/** reimplemented from QIODevice*/
qint64 QxtPipe::writeData ( const char * data, qint64 maxSize )
{
    qint64 r=0;

    foreach(QxtPipe* p,qxt_d().pipes)
    {
        qint64 e= p->receiveData(data,maxSize);
        if(e>r)
            r=e;
    }
    return r;
}


/** 
receiveData is called from any connected pipe to input data into this instance
*/
qint64 QxtPipe::receiveData ( const char * data, qint64 maxSize )
{
    QQueue<char> * q=&qxt_d().q;

    qint64 i=0;
    for (;i<maxSize;i++)
        q->enqueue(*data++);

    if (i>0)
        emit(readyRead ());
    return maxSize;
}

