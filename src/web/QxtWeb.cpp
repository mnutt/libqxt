#include <QxtWeb.h>
#include <QTcpSocket>
#include <QUrl>
#include <QStringList>
#include <QList>
#include <QByteArray>

QxtError QxtWeb::readContentFromSocket(QTcpSocket * tcpSocket,server_t & SERVER , post_t & POST)
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





QxtError QxtWeb::parseString(QByteArray content_in, post_t & POST)
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







