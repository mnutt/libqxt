#include "QxtWebCommunicator.h"
#include "QxtWebInternal.h"
#include "QxtWebWidget.h"
#include <QTcpSocket>

#include <QDebug>
#include <QMutexLocker>


QxtWebCommunicator::QxtWebCommunicator(QObject * parent):QObject(parent)
	{
	holdsocket=NULL;
	};




void QxtWebCommunicator::incoming(QTcpSocket * tcpSocket,QHash<QByteArray,QByteArray> SERVER)
	{
	if(!tcpSocket)return;



	///delete the current holding socket
// 	if(holdsocket)
// 		{
//  		holdsocket->write("Status: 204  No Content\r\n");
// 		holdsocket->write("Content-Type: text/html\r\n\r\n\r\n");	
// 		holdsocket->disconnectFromHost();
// 		holdsocket->waitForDisconnected();
// 		holdsocket->deleteLater();
// 		}

	///hold this one
	holdsocket=tcpSocket;



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




	///--------------sync ------------------
	QByteArray trace_in;
	QByteArray a =SERVER["HTTP_COOKIE"];
	QList<QByteArray> l= a.split(';');

	a="";
	foreach(a,l)
		{
		a=a.trimmed();
		if (a.startsWith("trace"))
			{
			trace_in=a.mid(6);
			break;
			}
		}
	
	QMutexLocker locker(&mutex); //this is for debug. if it deadlocks, we're doomed

	if (tracelist.remove(trace_in))  ///asume a sync
		{
		return;
		}




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

	QxtWebWidget * controller =qFindChild<QxtWebWidget *> ( parent(), path );
				

	if (!controller) 
		{
		QxtWebInternal::internalPage(4041,path,tcpSocket);
		return;
		}
	else
		{


		
		int retVal;
 		if (!QMetaObject::invokeMethod(controller, action,
				Q_RETURN_ARG(int, retVal)
				/*,Q_ARG(QString, QString())*/))

			{
			QxtWebInternal::internalPage(4042,action,tcpSocket,0,path);
			return;
			}
		


		}

	


	}





void QxtWebCommunicator::update()
	{
	if (!holdsocket)return;
	

	QTextStream stream(holdsocket);

	QxtWebWidget * w= reinterpret_cast<QxtWebWidget * >(QObject::sender());

	if (!w)return;

	QByteArray trace;
	do
		{trace=QByteArray(
				QByteArray::number(qrand())+
				QByteArray::number(qrand())
				);
		}
	while(tracelist.count(trace)>0);

	QMutexLocker locker(&mutex); //this is for debug. if it deadlocks, we're doomed
	tracelist[trace]="";


	stream<<"Status: 200 OK\r\n";
	stream<<"Content-Type: text/html\r\n";
 	stream<<"Set-Cookie: trace="<<trace<<"; path=/;\r\n";
	stream<<"\r\n\r\n";

	w->renderTo(stream);



	stream.flush (); 
	holdsocket->disconnectFromHost();
	holdsocket->waitForDisconnected();
	holdsocket->deleteLater();
	holdsocket=NULL;
	}









void QxtWebCommunicator::initAfterCreate()
	{
	}




