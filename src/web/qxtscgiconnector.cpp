#include "qxtscgiconnector.h"
#include <QTcpSocket>
#include <QTcpServer>
class QxtScgiConnectorPrivate : public QTcpServer,public QxtPrivate<QxtScgiConnector>
	{
	QXT_DECLARE_PUBLIC(QxtScgiConnector);

        protected:

                void incomingConnection ( int socketDescriptor )
                        {
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

                        emit(qxt_p().incomming(SERVER));
                        }

                QTcpSocket * socket_m;



int readHeaderFromSocket(QTcpSocket * tcpSocket,server_t & SERVER)
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






	};

QxtScgiConnector::QxtScgiConnector():QxtAbstractWebConnector()
        {
        QXT_INIT_PRIVATE(QxtScgiConnector);
        qxt_d().socket_m=0;
        }

int QxtScgiConnector::start (quint16 port,const QHostAddress & address)
        {
        return qxt_d().listen(address,port);
        }

QIODevice * QxtScgiConnector::socket()
        {
        return qxt_d().socket_m;
        }
void QxtScgiConnector::sendHeader(server_t & answer)
                {
                if(!answer.contains("Status"))
                        answer["Status"]="200 OK";
                if(!answer.contains("Content-Type"))
                        answer["Content-Type"]="text/html; charset=utf-8";

                server_t::const_iterator i = answer.constBegin();
                while (i != answer.constEnd()) 
                        {
                        qxt_d().socket_m->write(i.key()+": "+i.value()+"\r\n");
                        ++i;
                        }
                qxt_d().socket_m->write("\r\n");
                }

void  QxtScgiConnector::close()
        {
        emit(aboutToClose());
        qxt_d().socket_m->close();
        }





