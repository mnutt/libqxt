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





/*!
        \class QxtWebStatelessConnector QxtWebStatelessConnector
        \ingroup QxtWeb
        \brief new generation of connectors for stateless protocols with real eventbased handling.


        Usually you want to use an implementation of this class, such as QxtWebFcgiConnector or QxtWebHttpConnector. \n

        QxtWebStatelessConnector is the "daemon" instance that will listen for incomming connections for that protocoll. \n
        QxtWebStatelessConnection represents an actuall connection. It's a QIODevice, so you can perform I/O operations for the actuall http body. The header can be accesses via the uniformed QHttpResponseHeader and QHttpRequestHeader, defined fields might depend on protocoll though. \n \n
        
        When implementing your own connector, you have to implement all abstract functions from QxtWebStatelessConnection and QxtWebStatelessConnector.  Then you should return your custom QxtWebStatelessConnection in nextPendingConnection()
        \n \n


        direct use of the connectors is possible. see the follwing example:
        \code

        int main (int argc,char ** argv)
        {
            QCoreApplication app(argc,argv);

            QxtWebHttpConnector c;
            c.start ( 80, QHostAddress::LocalHost );

            forever
            {
                c.waitForNewConnection(-1);
                QxtWebStatelessConnection * st=c.nextPendingConnection();
                st->waitForReadyRead(10000);

                QTextStream stream(st);
                stream<<"<html><head>";
                stream<<"<title>"<<st->request().path()<<"</title>";
                stream<<"</head><body>";
                stream<<"<h1>HAI! I CAN HAZ HTML!</h1>";
                stream<<"</body></html>";
                stream.flush();
                delete (st);
            }
        }
        \endcode














        see also  QxtWebStatelessConnection

*/

/*!
        \class QxtWebStatelessConnection QxtWebStatelessConnector
        \ingroup QxtWeb
        \brief representing a connection from QxtWebStatelessConnector


        Usually you want to use an implementation of this class, such as QxtWebFcgiConnector or QxtWebHttpConnector. \n

        QxtWebStatelessConnector is the "daemon" instance that will listen for incomming connections for that protocoll. \n
        QxtWebStatelessConnection represents an actuall connection. It's a QIODevice, so you can perform I/O operations for the actuall http body. The header can be accesses via the uniformed QHttpResponseHeader and QHttpRequestHeader, defined fields might depend on protocoll though. \n \n
        
        When implementing your own connector, you have to implement all abstract functions from QxtWebStatelessConnection and QxtWebStatelessConnector.  Then you should return your custom QxtWebStatelessConnection in nextPendingConnection()

        see also  QxtWebStatelessConnector

*/


/*!
        \fn  virtual         QHttpResponseHeader & QxtWebStatelessConnection::response()        =0;
        access to the response header.  set any field you like here. 
        As soon as you write to the connection, the header is sent and any later modifications are lost. 
        \fn  virtual const   QHttpResponseHeader & QxtWebStatelessConnection::response() const  =0;
        convinince function
        \fn  virtual         QHttpRequestHeader & QxtWebStatelessConnection::request ()         =0;
        access to the request header. is invalid before the readyRead() signal is emited the first time
        \fn virtual const   QHttpRequestHeader & QxtWebStatelessConnection::request () const   =0;
        convinince function




        \fn virtual bool QxtWebStatelessConnector::isMultiplexing()=0;
        returns true when the implementation supports multiple connections \n
        if this is  false, you have to call close() on the connection before the next newConnection() can be emited
        \fn virtual bool QxtWebStatelessConnector::start (quint16 port,const QHostAddress & address)=0;
        starts the listener. implementation might vary
        \fn virtual QAbstractSocket::SocketError QxtWebStatelessConnector::serverError () const=0;
        returns the last error
        \fn virtual QxtWebStatelessConnection * QxtWebStatelessConnector::nextPendingConnection ()=0;
        Returns the next pending connection as a QxtWebStatelessConnection object.\n
        The socket is created as a child of the server, which means that it is automatically deleted when the QTcpServer object is destroyed. It is still a good idea to delete the object explicitly when you are done with it, to avoid wasting memory.\n
        0 is returned if this function is called when there are no pending connections. \n
        See also hasPendingConnections().\n

        \fn virtual bool QxtWebStatelessConnector::hasPendingConnections () const =0;
        Returns true if the server has a pending connection; otherwise returns false.
        \fn virtual bool QxtWebStatelessConnector::waitForNewConnection ( int msec = 0, bool * timedOut = 0 )=0;
        Waits for at most msec milliseconds or until an incoming connection is available. \n
        Returns true if a connection is available; otherwise returns false. If the operation timed out and timedOut is not 0, *timedOut will be set to true. \n
        This is a blocking function call. Its use is disadvised in a single-threaded GUI application, since the whole application will stop responding until the function returns. waitForNewConnection() is mostly useful when there is no event loop available. \n
        The non-blocking alternative is to connect to the newConnection() signal. \n
        See also hasPendingConnections() and nextPendingConnection(). \n
 */




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

