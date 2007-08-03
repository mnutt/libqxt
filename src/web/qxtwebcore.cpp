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
#include <QTcpSocket>
#include <QVariant>
/*!
        \class QxtWebCore QxtWebCore
        \ingroup web
        \brief qxtweb application core class. communicates, delegates, does all of the magic ;)


        QxtWebCore is the base class of your web application.
        it listens to the scgi protocoll

        construct one webcore object in the main function of your application.
        you must contruct it AFTER QCoreApplication and BEFORe any controllers.

        \code
        int main(int argc,char ** argv)
                {
                QCoreApplication  app(argc,argv);
                QxtWebCore core();
                core.listen(8080);
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
        \fn static QIODevice * socket();
        direct access to a iodevice for writing binary data.
        You shouldn't use that unless it's absolutly nessesary
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


        singleton_m=this;

	QXT_INIT_PRIVATE(QxtWebCore);
	}

QxtWebCore::~QxtWebCore()
        {
        singleton_m=0;
        }

QxtWebCore * QxtWebCore::instance()
        {
        if(!singleton_m)
                qFatal("no QxtWebCore constructed");
        return singleton_m;
        }
void QxtWebCore::send(QByteArray a)
        {
        instance()->qxt_d().send(a);
        }
void QxtWebCore::header(QByteArray a,QByteArray b)
        {
        instance()->qxt_d().header(a,b);
        }

server_t &  QxtWebCore::SERVER()
        {
        return instance()->qxt_d().currentservert;
        }

QIODevice * QxtWebCore::socket()
        {
        return instance()->qxt_d().socket_m;
        }

int QxtWebCore::listen (quint16 port ,const QHostAddress & address )
        {
        return qxt_d().listen(address,port);
        }



//-----------------------implementation----------------------------

QxtWebCorePrivate::QxtWebCorePrivate(QObject *parent):QTcpServer(parent)
        {
        }


void QxtWebCorePrivate::incomingConnection(int socketDescriptor)
        {
        header_sent=false;
        answer.clear();
        qDebug("%i, -> incomming",(int)time(NULL));
	QTcpSocket * tcpSocket = new QTcpSocket;
	if (!tcpSocket->setSocketDescriptor(socketDescriptor)) 
		{
		return;
		}
        socket_m=tcpSocket;
	connect(tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));

	server_t SERVER;
	int eee1=readHeaderFromSocket(tcpSocket,SERVER);

        if(eee1)
		{
                tcpSocket->write("Status: 500 INTERNAL SERVER ERROR\r\ncontent-type: text/html\r\n\r\nHEADER NOT READABLE");
		}


        qDebug("%i, %s -> %s",(int)time(NULL),SERVER["HTTP_HOST"].constData(),SERVER["REQUEST_URI"].constData());


        currentservert=SERVER;

        emit(qxt_p().request());

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
                tcpSocket->write("Status: 500 INTERNAL SERVER ERROR\r\ncontent-type: text/html\r\n\r\nERROR HANDLING NOT IMPLEMENTED");
		qDebug("controller '%s' not found",path.constData()); 
                return;
		}

	int i=controller->invoke(SERVER);
	if(i)
                {
                tcpSocket->write("Status: 500 INTERNAL SERVER ERROR\r\ncontent-type: text/html\r\n\r\nERROR HANDLING NOT IMPLEMENTED");
                }

        tcpSocket->disconnectFromHost();

        }


void QxtWebCorePrivate::sendheader()
        {
        if(!header_sent)
                {
                if(!answer.contains("Status"))
                        answer["Status"]="200 OK";
                if(!answer.contains("Content-Type"))
                        answer["Content-Type"]="text/html; charset=utf-8";

                server_t::const_iterator i = answer.constBegin();
                while (i != answer.constEnd()) 
                        {
                        socket_m->write(i.key()+": "+i.value()+"\r\n");
                        ++i;
                        }
                socket_m->write("\r\n");
                header_sent=true;
                }
        }

void QxtWebCorePrivate::header(QByteArray k ,QByteArray v)
        {
        answer[k]=v;
        }
void QxtWebCorePrivate::send(QByteArray a)
        {
        if(socket_m)
                {
                sendheader();
                socket_m->write(a);
                }
        else
		qDebug()<<"<send attemp when no connection open";
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






int QxtWebCorePrivate::readHeaderFromSocket(QTcpSocket * tcpSocket,server_t & SERVER)
	{
	if (!tcpSocket)
		return 5012;


	///--------------get the header size----------------
	
	QByteArray size_in;
	while(!size_in.endsWith(':'))
		{
		if(!tcpSocket->bytesAvailable ())
			if (!tcpSocket->waitForReadyRead (200))
                                return 50033;

		char a[4]; ///4? yes, i know i'm paranoid about bounds.


		if (!tcpSocket->read (a, 1 ))
                                return 50034;

		size_in+=a[0];

		if (size_in.size()>20)/// after the 20ths char is an attack atemp for sure
                                return 50034;

		}
	

	size_in.chop(1);
	int size=size_in.toInt()+1;


	if (size>10240)  ///do not accept headers over 10kb
                                return 50037;


	///--------------read the header------------------

	while(tcpSocket->bytesAvailable ()<size)
		{
		if (!tcpSocket->waitForReadyRead (200))
                                return 50033;
		}
	QByteArray header_in;
	header_in.resize(size);

	if (tcpSocket->read (header_in.data(), size )!=size)
                                return 50034;

	if (!header_in.endsWith(','))
                                return 50090;
	///--------------parse the header------------------


	int i=0;
	QByteArray name="";
	QByteArray a =header_in;
	while((i=a.indexOf('\0'))>-1)
		{
		if(name=="")
			{
			name= a.left(i).replace('\0',"");
			}
		else
			{
			SERVER[name]=a.left(i).replace('\0',"").replace("%20"," ");
			name="";
			}
		
		a=a.mid(i+1);
		}


        return 0;
	}
//---------------------------------------------------------------------------


















