#ifndef QxtWebCommunicatorHEaderCrappasljdnsaidnasd
#define QxtWebCommunicatorHEaderCrappasljdnsaidnasd



#include <QObject>
#include <QHash>
#include <QTextStream>
#include <QMutex>

class QTcpSocket;


class QxtWebCommunicator : public QObject
	{
	Q_OBJECT

	public:
		QxtWebCommunicator(QObject * parent);

		void initAfterCreate();


		void incoming(QTcpSocket * tcpSocket,QHash<QByteArray,QByteArray> SERVER);


	public slots:
		void update();


	private:
		QTcpSocket * holdsocket;
		QTextStream * stream;


		QHash<QByteArray,QByteArray> tracelist;


		QMutex mutex;

	};



#endif

