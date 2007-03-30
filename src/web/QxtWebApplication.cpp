#include "QxtWebApplication_p.h"
#include "QxtHtmlTemplate.h"
#include "QxtWebController.h"
#include "QxtWebInternal.h"
#include <QtNetwork>
#include <QDebug>
#include <QUrl>
#include <QTimer>

#include <QxtCore/QxtError>












///-----------------------interface----------------------------



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






///-----------------------private----------------------------


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

	///--------------get the header size----------------

	QByteArray size_in;
	while(!size_in.endsWith(':'))
		{
		if(!tcpSocket->bytesAvailable ())
			if (!tcpSocket->waitForReadyRead (200))
				{QxtWebInternal::internalPage(408,"Timeout while waiting for request data.",tcpSocket); return;}

		char a[4]; ///4? yes, i know i'm paranoid about bounds.


		if (!tcpSocket->read (a, 1 ))
			{QxtWebInternal::internalPage(500,"Socket I/O failure.",tcpSocket); return;}

		size_in+=a[0];

		if (size_in.size()>20)/// after the 20ths char is an attack atemp for sure
			{QxtWebInternal::internalPage(400,"The Overflow Protector has been triggered.",tcpSocket); return;}

		}
	

	size_in.chop(1);
	int size=size_in.toInt()+1;


	if (size>10240)  ///do not accept headers over 10kb
		{QxtWebInternal::internalPage(411,"Your Header was too long.",tcpSocket); return;}


	///--------------read the header------------------

	while(tcpSocket->bytesAvailable ()<size)
		{
		if (!tcpSocket->waitForReadyRead (200))
			{QxtWebInternal::internalPage(408,"Timeout while waiting for request data.",tcpSocket); return;}
		}
	QByteArray header_in;
	header_in.resize(size);

	if (tcpSocket->read (header_in.data(), size )!=size)
		{ QxtWebInternal::internalPage(500,"Socket I/O failure.",tcpSocket); return;}

	if (!header_in.endsWith(','))
		{
		QxtWebInternal::internalPage(501,"The Post method you tried is not supported.",tcpSocket);
		return;
		}
	///--------------parse the header------------------

	QHash<QByteArray, QByteArray> SERVER;

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
			SERVER[name]=a.left(i).replace('\0',"");
			name="";
			}
		
		a=a.mid(i+1);
		}


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



void QxtWebApplicationWorker::execute_request(QTcpSocket * tcpSocket,servertype SERVER)
	{
	if(!tcpSocket)return;


	///--------------read the content------------------
	QHash<QByteArray, QString> POST;

	int content_size= SERVER["CONTENT_LENGTH"].toInt();
	while(tcpSocket->bytesAvailable ()<content_size)
		{
		if (!tcpSocket->waitForReadyRead (10000))
			{
			QxtWebInternal::internalPage(408,"Timeout while waiting for request data.",tcpSocket);
			return;
			}
		}
	
	QByteArray content_in;
	content_in.resize(content_size);


	if (tcpSocket->read (content_in.data(), content_size )!=content_size)
		{
		QxtWebInternal::internalPage(500,"Socket I/O failure.",tcpSocket);
		return;
		}

	

	if (SERVER.count("CONTENT_TYPE"))
		if (SERVER ["CONTENT_TYPE"]!="application/x-www-form-urlencoded")
			{
			QxtWebInternal::internalPage(501,"The Post method you tried is not supported.",tcpSocket);
			return;
			}


	QList<QByteArray> posts = content_in.split('&');


	QByteArray post;
	foreach(post,posts)
		{
		QList<QByteArray> b =post.split('=');
		if (b.count()!=2)continue;
		POST[b[0]]=QUrl::fromPercentEncoding  ( b[1].replace("+","%20") );
		}





	///--------------find controller------------------
	
	QByteArray path="404";
	if(SERVER.count("PATH_INFO"))
		{
		QList<QByteArray> ssi = SERVER["PATH_INFO"].split('/');
		if (ssi.count()>1)
			{
			path=SERVER["PATH_INFO"].split('/').at(1);
			if (path.trimmed().isEmpty())path="root";
			}
		else if (ssi.count()>0) 
			path="root";
		}

	QxtWebController * controller =findChild<QxtWebController *>(path);

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


		QByteArray action="index";	
		if(SERVER.count("PATH_INFO"))
			{
			QList<QByteArray> ssi = SERVER["PATH_INFO"].split('/');
			if (ssi.count()>2)
				{
				action=SERVER["PATH_INFO"].split('/').at(2);
				if (action.trimmed().isEmpty())action="index";
				}
			else if (ssi.count()>1) 
				action="index";
			}

		
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
			stream << view.evaluate();
			}
		
		
		stream.flush ();
		tcpSocket->disconnectFromHost();
		tcpSocket->waitForDisconnected();
		tcpSocket->deleteLater();
		}

	}


