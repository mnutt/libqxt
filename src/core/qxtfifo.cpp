/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qxt library.
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

/**
\class QxtFifo QxtFifo

\ingroup QxtCore

\brief Simple Loopback QIODevice

read and write to the same object \n
emits a readyRead Signal. \n
usefull for loopback tests where QBuffer does not work.

\code
QxtFifo fifo;
 QTextStream (&fifo)<<QString("foo");
 QString a;
 QTextStream(&fifo)>>a;
 qDebug()<<a;
\endcode

*/

/**

\fn  QxtFifo::QxtFifo(QObject * parent=0);
constructs a new QxtFifo

\fn  virtual bool QxtFifo::isSequential () const;
\reimp

\fn virtual qint64 QxtFifo::bytesAvailable () const;
\reimp

\fn     virtual qint64 QxtFifo::readData ( char * data, qint64 maxSize );
\reimp

\fn     virtual qint64 QxtFifo::writeData ( const char * data, qint64 maxSize );
\reimp

*/


#include "qxtfifo.h"
#include <string.h>
#include <limits.h>
#include <QDebug>
#include <QQueue>
#include <qatomic.h>
#include <qbasicatomic.h>

struct QxtFifoNode
{
    QxtFifoNode(const char* data, int size) : content(data, size)
    {
        next = NULL;
    }

    QByteArray content;
    QBasicAtomicPointer<QxtFifoNode> next;
};

class QxtFifoPrivate : public QxtPrivate<QxtFifo>
{
public:
    QXT_DECLARE_PUBLIC(QxtFifo);
    QxtFifoPrivate()
    {
        head = tail = new QxtFifoNode(NULL, 0);
        available = 0;
    }

    QBasicAtomicPointer<QxtFifoNode> head, tail;
    QBasicAtomicInt available;
};

QxtFifo::QxtFifo(QObject *parent) : QIODevice(parent)
{
    QXT_INIT_PRIVATE(QxtFifo);
    setOpenMode(QIODevice::ReadWrite);
}

qint64 QxtFifo::readData(char * data, qint64 maxSize)
{
    int bytes = qxt_d().available, step;
    if (!bytes) return 0;
    if (bytes > maxSize) bytes = maxSize;
    int written = bytes;
    char* writePos = data;
    QxtFifoNode* node;
    while (bytes > 0)
    {
        node = qxt_d().head;
        step = node->content.size();
        if (step >= bytes)
        {
            int rem = step - bytes;
            memcpy(writePos, node->content.constData(), bytes);
            step = bytes;
            node->content = node->content.right(rem);
        }
        else
        {
            memcpy(writePos, node->content.constData(), step);
            qxt_d().head.fetchAndStoreOrdered(node->next);
            delete node;
            node = qxt_d().head;
        }
        writePos += step;
        bytes -= step;
    }
    qxt_d().available.fetchAndAddOrdered(-written);
    return written;
}

qint64 QxtFifo::writeData(const char * data, qint64 maxSize)
{
    if (maxSize > 0)
    {
        if (maxSize > INT_MAX) maxSize = INT_MAX; // qint64 could easily exceed QAtomicInt, so let's play it safe
        QxtFifoNode* newData = new QxtFifoNode(data, maxSize);
        qxt_d().tail->next.fetchAndStoreOrdered(newData);
        qxt_d().tail.fetchAndStoreOrdered(newData);
        qxt_d().available.fetchAndAddOrdered(maxSize);
        QMetaObject::invokeMethod(this, "bytesWritten", Qt::QueuedConnection, Q_ARG(qint64, maxSize));
        QMetaObject::invokeMethod(this, "readyRead", Qt::QueuedConnection);
    }
    return maxSize;
}

bool QxtFifo::isSequential() const
{
    return true;
}

qint64 QxtFifo::bytesAvailable() const
{
    return qxt_d().available;
}

void QxtFifo::clear()
{
    qxt_d().available.fetchAndStoreOrdered(0);
    qxt_d().tail.fetchAndStoreOrdered(qxt_d().head);
    QxtFifoNode* node = qxt_d().head->next.fetchAndStoreOrdered(NULL);
    while (node && node->next)
    {
        QxtFifoNode* next = node->next.fetchAndStoreOrdered(NULL);
        delete node;
        node = next;
    }
    qxt_d().head->content = QByteArray();
}
