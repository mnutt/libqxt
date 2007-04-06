#include "QxtWebCommunicator.h"
#include "QxtWebInternal.h"
#include "QxtWebWidget.h"
#include <QTcpSocket>



QxtWebCommunicator::QxtWebCommunicator(QObject * parent):QObject(parent)
	{};




void QxtWebCommunicator::incoming(QTcpSocket * tcpSocket,QHash<QByteArray,QByteArray> SERVER)
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
		

		///temporary sync

 		controller->renderTo(tcpSocket);
		tcpSocket->disconnectFromHost();
		tcpSocket->waitForDisconnected();
		tcpSocket->deleteLater();
		}


	}

bool QxtWebCommunicator::openWriteStream(QTextStream * stream)
	{
	}

void QxtWebCommunicator::closeWriteStream()
	{
	}

