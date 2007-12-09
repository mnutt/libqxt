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
#include "qxtwebscgiconnector.h"
#include "qxtwebscgiconnector_p.h"

#include <QTcpSocket>
#include <QTcpServer>
#include <QtDebug>
#include <ctime>
#include <QDebug>



/*!
        \class QxtWebScgiConnector QxtWebScgiConnector
        \ingroup QxtWeb
        \brief QxtWebStatelessConnector for SCGI

        see QxtWebStatelessConnector
*/

QxtWebScgiConnector::QxtWebScgiConnector(QObject * parent  ):QxtWebStatelessConnector(parent)
{
        connect(&qxt_d(),SIGNAL(newConnection()),this,SIGNAL(newConnection()));
}

bool QxtWebScgiConnector::start ( quint16 port, const QHostAddress & address)
{
    return qxt_d().listen(address,port);
}


QAbstractSocket::SocketError QxtWebScgiConnector::serverError () const
{
    return qxt_d().serverError();
}

QxtWebStatelessConnection * QxtWebScgiConnector::nextPendingConnection ()
{
    if(!hasPendingConnections())
        return 0;

    QxtWebScgiConnection * n= new QxtWebScgiConnection(qxt_d().nextPendingConnection(),this);
    return n;
}

bool QxtWebScgiConnector::hasPendingConnections () const
{
    return qxt_d().hasPendingConnections();

}

bool QxtWebScgiConnector::waitForNewConnection ( int msec , bool * timedOut  )
{
    return qxt_d().waitForNewConnection(msec,timedOut);
}





qint64 QxtWebScgiConnection::writeData ( const char * data, qint64 maxSize )
{
    if(!headerReceived)
    {
        qWarning("QxtWebScgiConnection trying to write before headers could be received might fail.");
    }

    if(!headerSent)
    {
        m_socket->write(("Status:"+QString::number(response_m.statusCode ())+" "+response_m.reasonPhrase ()+"\r\n").toAscii());
        foreach(QString key, response_m.keys())
        {
            m_socket->write((key+":"+response_m.value(key)+"\r\n").toAscii());
        }
        m_socket->write("\r\n");
    }
    return m_socket->write(data,maxSize);
}


void QxtWebScgiConnection::readyreadslot()
{
    if(headerReceived)
    {
        emit(readyRead());
        return;
    }



    while (m_socket->bytesAvailable())
    {
        if (headerBytesReceived++ > 10024) //10kb max
        {
            qWarning("QxtWebScgiConnection. header > 10kb. killed");
            close();
        }


        if(expectedheaderBytes)
        {
            QByteArray a; 
            a.resize(expectedheaderBytes);
            int rec=m_socket->read(a.data(),expectedheaderBytes-headerBytesReceived);
            a.resize(rec);
            bbuf+=a;
            headerBytesReceived+=rec;
            if(headerBytesReceived==expectedheaderBytes)
            {
                char nowhere [4];
                m_socket->read(nowhere,3); ///read the tailing comma 

                int i=0;
                QByteArray name="";
                QByteArray a =bbuf;
                while ((i=a.indexOf('\0'))>-1)
                {
                    if (name=="")
                    {
                        name= a.left(i);
                    }
                    else
                    {
                        request_m.setValue (QString::fromAscii(name).toLower(),QString::fromAscii(a.left(i)));
                        name="";
                    }
                    a=a.mid(i+1);
                }


                request_m.setRequest (request_m.value("request_method"),request_m.value("request_uri"));
                bbuf.clear();
                headerReceived=true;
                if(m_socket->bytesAvailable())
                    readyreadslot();
                return;
            }
        }
        else
        {
            char a;
            if(m_socket->read ( &a,1)!=1)
            {
                qCritical("QxtWebScgiConnection  socket I/O error. killed");
                close();
            }


            if(a==':')
            {
                expectedheaderBytes=bbuf.toInt();
                headerBytesReceived=0;
                bbuf.clear();
            }
            else if (headerBytesReceived++ > 10)
            {
                qWarning("QxtWebScgiConnection. not received size prefix withing 10 chars. killed");
                close();
            }
            else
            {
                bbuf+=a;
            }
        }
    }
}

