#include "QxtWebCommunicator.h"
#include "QxtWebInternal.h"
#include "QxtWebWidget.h"
#include <QTcpSocket>



QxtWebCommunicator::QxtWebCommunicator(QObject * parent):QObject(parent)
	{
	holdsocket=NULL;
	stream=NULL;
	};




void QxtWebCommunicator::incoming(QTcpSocket * tcpSocket,QHash<QByteArray,QByteArray> SERVER)
	{
	if(!tcpSocket)return;

	///delete the current holding socket
	if(holdsocket)
		{
		holdsocket->write("204  No Content\r\n");
		holdsocket->write("Content-Type: text/html\r\n\r\n\r\n");	
		holdsocket->disconnectFromHost();
		holdsocket->waitForDisconnected();
		holdsocket->deleteLater();
		}

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
int QxtWebCommunicator::getwriteChannel(QTextStream ** s)
	{
	if (!holdsocket)return 0;
	if (!stream)
		{
		stream=new QTextStream(holdsocket);	
		}


	*s=stream;	
	return 1;
	}

void QxtWebCommunicator::closeWriteChannel(int )
	{
	if (!holdsocket)return;
	if (stream){stream->flush (); delete stream; stream=NULL;}

	holdsocket->disconnectFromHost();
	holdsocket->waitForDisconnected();
	holdsocket->deleteLater();
	holdsocket=NULL;	
	}




void QxtWebCommunicator::update()
	{
	qDebug("update");
	QxtWebWidget * w= reinterpret_cast<QxtWebWidget * >(QObject::sender());
	QTextStream * stream;
	if (!getwriteChannel(&stream))return;
	w->renderTo(*stream);
	closeWriteChannel(0);
	}
