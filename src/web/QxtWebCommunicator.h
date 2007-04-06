#ifndef QxtWebCommunicatorHEaderCrappasljdnsaidnasd
#define QxtWebCommunicatorHEaderCrappasljdnsaidnasd



#include <QObject>
#include <QHash>
#include <QTextStream>

class QTcpSocket;


class QxtWebCommunicator : public QObject
	{
	Q_OBJECT

	public:
		QxtWebCommunicator(QObject * parent);




		void incoming(QTcpSocket * tcpSocket,QHash<QByteArray,QByteArray> SERVER);


		bool openWriteStream(QTextStream * stream);
		void closeWriteStream();

	public:
		QTcpSocket * holdsocket;


	};



#endif

