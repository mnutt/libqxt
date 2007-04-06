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


		int getwriteChannel(QTextStream ** stream);
		void closeWriteChannel(int c);



	public slots:
		void update();


	private:
		QTcpSocket * holdsocket;
		QTextStream * stream;



	};



#endif

