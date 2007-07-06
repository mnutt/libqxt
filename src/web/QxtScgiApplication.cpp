#include "QxtScgiApplication_p.h"
#include "QxtScgiController.h"

#include <QtNetwork>
#include <QDebug>
#include <QTimer>
#include <QxtError.h>


#define senderror(errorpath)     {    SERVER["REQUEST_URI"]=errorpath;  \
                        int i=errorhandler->invoke(tcpSocket,SERVER); \
                        if(i!=0) \
                                { \
                                qDebug("the error handler apears to be broken (return code: %i )",i); \
                                abort(); \
                                } }



//-----------------------interface----------------------------

QxtScgiApplication::QxtScgiApplication ( int & argc, char ** argv ):QCoreApplication(argc,argv)
	{
	qRegisterMetaType<server_t>("server_t");
	QXT_INIT_PRIVATE(QxtScgiApplication);
	}

int QxtScgiApplication::exec (quint16 port,const QHostAddress & address)
        {
        qxt_d().init();
	if (!qxt_d().listen (address,port))
		{
		qDebug("listen failed, %s",qPrintable(qxt_d().errorString()));
                return 12;
		}
        return QCoreApplication::exec();
	};



//-----------------------private----------------------------


QxtScgiApplicationPrivate::QxtScgiApplicationPrivate(QObject *parent) : QTcpServer(parent) 
	{
        errorhandler=NULL;
	}
void QxtScgiApplicationPrivate::init()
        {
	errorhandler= qFindChild<QxtScgiController *> (&qxt_p(), "error" );
        if (!errorhandler)
                {
		qDebug("missing an error controller");
                abort();
                }
        }

//---------------------------------------------------------------------------


void QxtScgiApplicationPrivate::incomingConnection(int socketDescriptor)
	{
	QTcpSocket * tcpSocket = new QTcpSocket;
	if (!tcpSocket->setSocketDescriptor(socketDescriptor)) 
		{
		return;
		}
	connect(tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));


	server_t SERVER;
	QXT_DROP_SCOPE(error,SCGI::header(tcpSocket,SERVER))
		{
                senderror("/error/index/500/");
		return;
		};


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

	QxtScgiController * controller =qFindChild<QxtScgiController *> (&qxt_p(), path );
	if (!controller) 
		{
                senderror("/error/index/4041/"+path);
		return;
		}
	else
                {
                int i=controller->invoke(tcpSocket,SERVER);
                if(i)
                        {
                        senderror("/error/index/"+QString::number(i).toUtf8()+"//"+path);
                        }
                }


	tcpSocket->disconnectFromHost();
	}






//----------------------------SCGI--------------------------------





QxtError SCGI::header(QTcpSocket * tcpSocket,server_t & SERVER)
	{
	if (!tcpSocket)
		QXT_DROP(Qxt::UnexpectedNullParameter);


	///--------------get the header size----------------
	
	QByteArray size_in;
	while(!size_in.endsWith(':'))
		{
		if(!tcpSocket->bytesAvailable ())
			if (!tcpSocket->waitForReadyRead (200))
				QXT_DROP(Qxt::ClientTimeout);

		char a[4]; ///4? yes, i know i'm paranoid about bounds.


		if (!tcpSocket->read (a, 1 ))
				QXT_DROP(Qxt::SocketIOError);

		size_in+=a[0];

		if (size_in.size()>20)/// after the 20ths char is an attack atemp for sure
				QXT_DROP(Qxt::ParserError);

		}
	

	size_in.chop(1);
	int size=size_in.toInt()+1;


	if (size>10240)  ///do not accept headers over 10kb
				QXT_DROP(Qxt::HeaderTooLong);


	///--------------read the header------------------

	while(tcpSocket->bytesAvailable ()<size)
		{
		if (!tcpSocket->waitForReadyRead (200))
				QXT_DROP(Qxt::ClientTimeout);
		}
	QByteArray header_in;
	header_in.resize(size);

	if (tcpSocket->read (header_in.data(), size )!=size)
				QXT_DROP(Qxt::SocketIOError);

	if (!header_in.endsWith(','))
		QXT_DROP_S(Qxt::NotImplemented,"This Post method is not supported.");

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
			SERVER[name]=a.left(i).replace('\0',"");
			name="";
			}
		
		a=a.mid(i+1);
		}


	QXT_DROP_OK
	}
//---------------------------------------------------------------------------


#if 0
bool QxtWebInternal::readScgiContentFromSocket(QTcpSocket * tcpSocket,int content_size, QString contentType ,QHash<QString,QString> & POST)
	{
	if (!tcpSocket)return false;

	if (!content_size)
		{
		return true;
		}


	///--------------read the content------------------

	while(tcpSocket->bytesAvailable ()<content_size)
		{
		if (!tcpSocket->waitForReadyRead (10000))
			{
			QxtWebInternal::internalPage(408,"Timeout while waiting for request data.",tcpSocket);
			return false;
			}
		}
	
	QByteArray content_in;
	content_in.resize(content_size);


	if (tcpSocket->read (content_in.data(), content_size )!=content_size)
		{
		QxtWebInternal::internalPage(500,"Socket I/O failure.",tcpSocket);
		return false;
		}

	
	if (contentType!="application/x-www-form-urlencoded")
		{
		QxtWebInternal::internalPage(501,"The Post method you tried is not supported.",tcpSocket);
		return false;
		}


	QList<QByteArray> posts = content_in.split('&');


	QByteArray post;
	foreach(post,posts)
		{
		QList<QByteArray> b =post.split('=');
		if (b.count()!=2)continue;

		

		POST[QUrl::fromPercentEncoding  ( b[0].replace("+","%20"))]=QUrl::fromPercentEncoding  ( b[1].replace("+","%20") );
		}




	
	return true;

	}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#endif




