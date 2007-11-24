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

/*
this is a private header. it's written without reusability in mind.
If you include this in your application, you're already doomed.
*/


#include "qxtwebscgiconnector.h"
#include <QTcpSocket>
#include <QTcpServer>


class QxtWebScgiConnectorPrivate : public QTcpServer,public QxtPrivate<QxtWebScgiConnector>
{
    QXT_DECLARE_PUBLIC(QxtWebScgiConnector);
};




class QxtWebScgiConnection  : public QxtWebStatelessConnection
{
Q_OBJECT
public:
    virtual const   QHttpResponseHeader & response() const
    {
        return response_m;
    }

    virtual         QHttpResponseHeader & response()
    {
        return response_m;
    }

    virtual const   QHttpRequestHeader & request () const
    {
        return request_m;
    }

    virtual         QHttpRequestHeader & request ()
    {
        return request_m;
    }

    virtual bool isSequential () const
    {
        return true;
    }
    virtual bool open ( OpenMode  )
    {
        qWarning("QxtWebScgiConnection::open has no effect");
        return false;
    }

    virtual bool reset ()
    {
        return m_socket->reset();
    }

    virtual qint64 size () const
    {
        if(!headerReceived)
            return 0;

        return m_socket->size();
    }
    virtual bool waitForReadyRead ( int msecs )
    {
        bool d=m_socket->waitForReadyRead(msecs);

        if (!d)
            return false;

        if(endAllRecursionsSinceTerminated)
            return false;

        if (!headerReceived)
            return waitForReadyRead(msecs);

        return true;
    }

    virtual qint64 bytesAvailable () const
    {
        if(!headerReceived)
            return 0;

        return m_socket->bytesAvailable();
    }
    virtual qint64 bytesToWrite () const
    {
        if(!headerReceived)
            return 0;
        return m_socket->bytesToWrite();
    }


    virtual void close ()
    {
        endAllRecursionsSinceTerminated=true;
        m_socket->flush();
        m_socket->disconnectFromHost();
        m_socket->close();
    }



    ~QxtWebScgiConnection()
    {
        close();
        setOpenMode(m_socket->openMode());
        delete m_socket;
    }

private slots:
    void readyreadslot();

private:
    friend class QxtWebScgiConnector;

    QxtWebScgiConnection(QTcpSocket * socket, QObject *parent):QxtWebStatelessConnection(parent)
    {
        headerBytesReceived=0;
        expectedheaderBytes=0;

        endAllRecursionsSinceTerminated=false;
        lastwasnewline=false;
        headerReceived=false;
        headerSent=false;
        m_socket=socket;
        setOpenMode(m_socket->openMode());


        response_m=QHttpResponseHeader ( 200, "OK");
        response_m.setContentType("text/html");

        connect(m_socket,SIGNAL(readyRead()),this,SLOT(readyreadslot()));
        connect(m_socket,SIGNAL(aboutToClose()),this,SIGNAL(aboutToClose()));

    }
    QTcpSocket * m_socket;

    QHttpResponseHeader response_m;
    QHttpRequestHeader request_m;

    bool headerReceived;
    int expectedheaderBytes;
    bool headerSent;

    int headerBytesReceived;
    bool lastwasnewline;
    QByteArray bbuf;

    bool endAllRecursionsSinceTerminated;
protected:

    virtual qint64 readData ( char * data, qint64 maxSize )
    {
        if(!headerReceived)
            return 0;
        return m_socket->read(data,maxSize);
    }





    virtual qint64 writeData ( const char * data, qint64 maxSize );
};

