/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/

#include "QxtWebApplication_p.h"
#include "QxtHtmlTemplate.h"
#include "QxtWebController.h"
#include "QxtWebInternal.h"
#include <QtNetwork>
#include <QDebug>
#include <QTimer>

#include <QxtCore/QxtError>

#include <QMetaObject>
#include <QMetaMethod>


/*!
	\class QxtWebApplication QxtWebApplication
	\ingroup web
	\brief The Core of QxtWeb


	starts a scgi client server listening to scgi connections, and handles all of request handling \n

	You need to define a callback function for the user threads. That callback gets a pointer to the Object the Controllers or any other session persistent data you need will live on. Always define a controller with the name "root".
	\code
	void webmain(QObject * space)
        	{
        	new QxtWebController(space,"root");
        	}

	int main(int argc, char *argv[])
        	{
        	QCoreApplication app(argc, argv);
        	QxtWebApplication server(&webmain);


        	QXT_DROP_SCOPE(error,server.listen(QHostAddress::Any,4000))
                	{
                	qDebug("Unable to start the server: %s.",error.errorString());
                	return 0;
                	}	

        	return app.exec();
        	}

	\endcode


*/



//-----------------------interface----------------------------



QxtWebApplication::QxtWebApplication(void (*callback)(QObject *),QObject * parent):QObject(parent)
	{
	if(!callback)
		{
		qWarning("the callback function canot be null!");
		return;
		}
	QXT_INIT_PRIVATE(QxtWebApplication);
	qxt_d().init(callback);
	}

QxtError QxtWebApplication::listen(const QHostAddress & address, quint16 port)
	{
	if (!qxt_d().listen (address,port))
		{
		
		QByteArray * a = new QByteArray(qxt_d().errorString().toLocal8Bit()); ///TODO: now this sucks
		QXT_DROP_S( Qxt::SeeErrorString,a->data());
		}
	QXT_DROP_OK
	};






//-----------------------private----------------------------


QxtWebApplicationPrivate::QxtWebApplicationPrivate(QObject *parent) : QTcpServer(parent) 
	{
	qRegisterMetaType<servertype>("servertype");
	qRegisterMetaType<QxtHtmlTemplate  *>("QxtHtmlTemplate  *");
	
	}
//---------------------------------------------------------------------------

void QxtWebApplicationPrivate::init(void (*callback)(QObject *)) 
	{
	callback_m= callback;
	}

//---------------------------------------------------------------------------

void QxtWebApplicationPrivate::incomingConnection(int socketDescriptor)
	{
	/**
	we first read the header here, so we can determinate what thread belongs to this request (or create a new one).
	it's safe to do it in the server application becouse scgi will send us the request AFTER the client finished sending it. that is fast enought to not block calls.
	the post content should not be read here, it may be very long and i'm not sure if scgi buffers it.
	becouse sgci should send us the data very fast we can use short timeouts here.

	TODO:regardless from the above statement we should use async signals'n'slots here to be absolutly sure
	*/

	QTcpSocket * tcpSocket = new QTcpSocket;
	if (!tcpSocket->setSocketDescriptor(socketDescriptor)) 
		{
		return;
		}

	QHash<QByteArray, QByteArray> SERVER;
	if (!QxtWebInternal::readScgiHeaderFromSocket(tcpSocket,SERVER))return;

	QxtWebApplicationThread *thread;
	
	
	///search cookie database for the coresponsing thread
	
	QByteArray f_mint;
 	if (SERVER.count("HTTP_COOKIE"))
 		{
 		QByteArray a =SERVER["HTTP_COOKIE"];
 		QList<QByteArray> l= a.split(';');

		a="";
		foreach(a,l)
			{
			a=a.trimmed();
			
			if (a.startsWith("mint"))
				{
				f_mint=a.mid(5);
				break;
				}
			}
 		}
	

	///TODO: this all is still a serious security hole. an attacker could easily spawn an unlimited amount of threads



	///look if the user is known
	if (!f_mint.isEmpty() && mints.count(f_mint))
		{
		qDebug()<<"welcome back"<<f_mint;

		thread=mints[f_mint];
		if(!thread)
			{
			///we give the user a thread now he proved sending us the mint

			thread = new QxtWebApplicationThread(callback_m,f_mint,this);
			connect(thread, SIGNAL(finished()), this, SLOT(threadfinished()));
			thread->start();
			mints[f_mint]=thread;
			qDebug()<<"mint "<<f_mint<<" is now on thread "<<thread;

			};

		if (!thread){qWarning("i failed to create a thread");return;}

		thread->request(tcpSocket,SERVER);
		}

	else	///if there is none found create a new one

		{
		QByteArray mint;

		do
			{mint=QByteArray(				///TODO: secure randomness
					QByteArray::number(qrand())+
					QByteArray::number(qrand())
					);
			}
		while(mints.count(mint)>0);
	
	
		///and tell the browser to send it back. ( show the "new mint page")

		qDebug()<<"proposing "<<mint<<"to"<<SERVER["REMOTE_ADDR"];
		mints[mint]=0;
		QxtWebInternal::internalPage(12345,mint,tcpSocket,&SERVER);
		}


	}


//---------------------------------------------------------------------------



void  QxtWebApplicationPrivate::threadfinished()
	{
	QxtWebApplicationThread * f =  dynamic_cast<QxtWebApplicationThread *>(QObject::sender ());
	if (!f)return;
	qDebug("%p finished",QObject::sender ());

	mints.remove(f->mint());
	f->deleteLater();
	}



//---------------------------------------------------------------------------






 QxtWebApplicationThread::QxtWebApplicationThread(void (*callback)(QObject *),QByteArray mint,QObject *parent)
     : QThread(parent)
	{
	communicator=NULL;
	mint_m=mint;
	callback_m=callback;
	firstrun=true;
	
	lifetime_m=120000;

	connect(&lifetime,   SIGNAL(timeout()),this, SLOT  (quit()));
	lifetime.start(lifetime_m);
	
	}
//---------------------------------------------------------------------------







 void QxtWebApplicationThread::run()
	{
	QxtWebApplicationWorker worker;


	(*callback_m)(&worker);
 
	///connecting signals to the client

	communicator  =qFindChild<QxtWebCommunicator *> (&worker);
	if (!communicator)
		{
		qWarning("Yu didnt specify a comunicator. defaulting to built in");
		communicator=new QxtWebCommunicator;
		}

	worker.communicator=communicator;
// 	QList<QxtWebController *> controllers= qFindChildren<QxtWebController *> (&worker);
// 
// 	QxtWebController * controller;
// 	foreach(controller,controllers)
// 		{
// 		const QMetaObject* meta= controller->metaObject ();
// 		
// 		int count= meta->methodCount ();
// 
// 		for (int i=QxtWebController::staticMetaObject.methodCount() ;i < count;i++)
// 			{
// 			QMetaMethod method=  meta->method (i);
// 			if (method.methodType ()!=QMetaMethod::Signal)continue;
// 
// 			connect(controller,qPrintable("2"+QString (method.signature ())),communicator,SLOT(update()));
// 
// 			}
// 		}


	connect(
		this,   SIGNAL(signal_request_to_worker(QTcpSocket *,servertype)),
		&worker, SLOT  (execute_request(QTcpSocket * ,servertype))
		);

     	started.wakeAll();

	if (exec()!=0)
		qDebug("%p ended unexpected!",this);
	}


//--------------------------------------------------------------------------


void QxtWebApplicationThread::request(QTcpSocket * socket,servertype &SERVER)
	{
	lifetime.stop();lifetime.start(lifetime_m); ///reset lifetime

	started_m.lock();

	if(firstrun)
		if (!started.wait(&started_m,10))
			{
			qWarning("I wanted to push your request to the worker, but i failed waiting on the worker beeing created.");
			}

	socket->moveToThread(this);
	emit(signal_request_to_worker(socket,SERVER));

	firstrun=false;
	started_m.unlock();
	}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

QxtWebApplicationWorker::QxtWebApplicationWorker()
	{
	communicator=NULL;
	}


void QxtWebApplicationWorker::execute_request(QTcpSocket * tcpSocket,servertype SERVER)
	{
	if(!tcpSocket)return;

	QHash<QString, QString> POST;
	if (!QxtWebInternal::readScgiContentFromSocket(tcpSocket,SERVER["CONTENT_LENGTH"].toInt(),SERVER["CONTENT_TYPE"],POST))return;


	///--------------find controller ------------------
	

	QByteArray path="404";
	QList<QByteArray> requestsplit = SERVER["PATH_INFO"].split('/');
	
	if (requestsplit.count()>1)
		{
		path=requestsplit.at(1);
		if (path.trimmed().isEmpty())path="root";
		}
	else if (requestsplit.count()>0) 
		path="root";


	///--------------find action ------------------
	QByteArray action="index";	
	
	if (requestsplit.count()>2)
		{
		action=requestsplit.at(2);
		if (action.trimmed().isEmpty())action="index";
		}
	else if (requestsplit.count()>1) 
		action="index";





	///--------------controller------------------

	QxtWebController * controller =qFindChild<QxtWebController *> ( this, path );
				

	if (!controller) 
		{
		QxtWebInternal::internalPage(4041,path,tcpSocket);
		return;
		}
	else
		{
		QxtHtmlTemplate  view;
		QTextStream  stream(tcpSocket);

		///push the request to the controller
		controller->push(SERVER,POST,&view,&stream);




		
		int retVal;
 		if (!QMetaObject::invokeMethod(controller, action,
				Q_RETURN_ARG(int, retVal)
				/*,Q_ARG(QString, QString())*/))

			{
			QxtWebInternal::internalPage(4042,action,tcpSocket,0,path);
			return;
			}
		
		if (retVal>-1)
			{
			if (!view.open(QxtWebInternal::WebRoot()+"/view/"+path+"/"+action+".html"))
				{
				QxtWebInternal::internalPage(4043,action,tcpSocket,0,path);
				return;
				}	
			stream << "Status: 200 OK\r\n";
			stream << "Content-Type: text/html\r\n\r\n";
			stream << view.render();
			}
		
		
		stream.flush ();
		tcpSocket->disconnectFromHost();
		tcpSocket->waitForDisconnected();
		tcpSocket->deleteLater();
		}

	}


