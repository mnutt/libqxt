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
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/
#include "qxtwebcore.h"
#include "qxtwebcore_p.h"
#include <QTimer>
#include <QUrl>
#include "qxtwebcontroller.h"
#include <QCoreApplication>
/*!
        \class QxtWebCore QxtWebCore
        \ingroup web
        \brief qxtweb application core class. communicates, delegates, does all of the magic ;)


        QxtWebCore is a lighweight class using QxtRPCPeer and QxtStdio. It Provides your Application 
        with an interface to a transport such as mod_qt , sige or any other implementation of it, and does the controller delegation for you.

        construct one webcore object in the main function of your application.
        you must contruct it AFTER QCoreApplication and BEFORe any controllers.

        \code
        int main(int argc,char ** argv)
                {
                QCoreApplication  app(argc,argv);
                QxtWebCore core;
                QxtWebController controller("root");
                app.exec();
                }
        \endcode
*/

/*!
        \fn static QxtWebCore* instance();
        singleton accessor
        \fn static void send(QByteArray);
        Send data to the client. Use this rarely, but use it always when sending binary data such as images.
        normal text/html comunication should be done using the controllers echo() function
        note that after you called send the first time you cannot modify the header anymore
        sending may be ignored by the transport when there is no client currently handled
        \fn static QxtRPCPeer * peer();
        direct access to the QxtRPCPeer used for communicating with the transport
        the returned pointer is valid during the whole lifetime of the program
        when subclassing QxtWebCore this can be used to implement a different protocoll
        \fn static QxtError parseString(QByteArray str, post_t & POST);
        much like phps parse_string
 */


static QxtWebCore * singleton_m=0;

//-----------------------interface----------------------------
QxtWebCore::QxtWebCore():QObject()
	{
        if(singleton_m)
                qFatal("you're trying to construct QxtWebCore twice!");
	qRegisterMetaType<server_t>("server_t");
        qRegisterMetaTypeStreamOperators<server_t>("server_t");
	QXT_INIT_PRIVATE(QxtWebCore);
        qxt_d().init();
	}


QxtWebCore * QxtWebCore::instance()
        {
        if(!singleton_m)
                singleton_m=new QxtWebCore;
        return singleton_m;
        }
void QxtWebCore::send(QByteArray a)
        {
        peer()->call(SIGNAL(send(QByteArray)),a);
        }
void QxtWebCore::header(QByteArray a,QByteArray b)
        {
        peer()->call(SIGNAL(header(QByteArray,QByteArray)),a,b);
        }

QxtRPCPeer * QxtWebCore::peer()
        {
        return instance()->qxt_d().peer;
        }

//-----------------------implementation----------------------------

QxtWebCorePrivate::QxtWebCorePrivate(QObject *parent):QObject(parent)
        {
        peer=new QxtRPCPeer(new QxtStdio(this));
        }
void QxtWebCorePrivate::init()
        {
        QTimer::singleShot(10,this,SLOT(startup()));
        };

void  QxtWebCorePrivate::request(server_t SERVER)
        {
        qDebug("%s",SERVER["REQUEST_URI"].constData());


	///--------------find controller ------------------
	QByteArray path="404";
	QList<QByteArray> requestsplit = SERVER["REQUEST_URI"].split('/');
	if (requestsplit.count()>1)
		{
		path=requestsplit.at(1);
		if (path.trimmed().isEmpty())path="root";
		}
	else if (requestsplit.count()>0) 
		path="root";

	///--------------controller------------------

	QxtWebController * controller =qFindChild<QxtWebController *> (QCoreApplication::instance(), path );
	if (!controller) 
		{
                peer->call(SIGNAL(header(QByteArray,QByteArray)),"Status","404");
                peer->call(SIGNAL(send(QByteArray)),QByteArray("<h1>controller  "+path+" not found</h1>"));
                peer->call(SIGNAL(close()));
                peer->call(SIGNAL(ready()));
		qDebug("controller '%s' not found",path.constData()); 
                return;
		}

	int i=controller->invoke(SERVER);
	if(i)
                {
                peer->call(SIGNAL(header(QByteArray,QByteArray)),"Status","500");
                peer->call(SIGNAL(send(QByteArray)),QByteArray("<h1>stupid me, no implementation for error codes!</h1>"));
                }

        peer->call(SIGNAL(close()));
        peer->call(SIGNAL(ready()));
        }
void  QxtWebCorePrivate::startup()
        {
        peer->attachSlot (SIGNAL(request(server_t)),this ,SLOT(request(server_t)));
        peer->call(SIGNAL(ready()));
        }

//-----------------------helper----------------------------

#if 0
QxtError QxtWebCore::readContentFromSocket(QTcpSocket * tcpSocket,server_t & SERVER , post_t & POST)
	{
	if (!tcpSocket)
		QXT_DROP(Qxt::UnexpectedNullParameter);


        int content_size=SERVER["CONTENT_LENGTH"].toInt();

	if (content_size<1)
		{
		QXT_DROP_OK
		}


	///--------------read the content------------------

	while(tcpSocket->bytesAvailable ()<content_size)
		{
		if (!tcpSocket->waitForReadyRead (10000))
                        QXT_DROP(Qxt::ClientTimeout);
		}
	
	QByteArray content_in;
	content_in.resize(content_size);


	if (tcpSocket->read (content_in.data(), content_size )!=content_size)
				QXT_DROP(Qxt::SocketIOError);


	
	if (SERVER["CONTENT_TYPE"]!="application/x-www-form-urlencoded")
		QXT_DROP_S(Qxt::NotImplemented,"This Post method is not supported.");


        QXT_DROP_F(parseString(content_in,POST));
	QXT_DROP_OK
	}



#endif

QxtError QxtWebCore::parseString(QByteArray content_in, post_t & POST)
	{
	QList<QByteArray> posts = content_in.split('&');
	QByteArray post;
	foreach(post,posts)
		{
		QList<QByteArray> b =post.split('=');
		if (b.count()!=2)continue;
		POST[QUrl::fromPercentEncoding  ( b[0].replace("+","%20"))]=QUrl::fromPercentEncoding  ( b[1].replace("+","%20") );
		}
	QXT_DROP_OK
	}
