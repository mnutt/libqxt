#include <QObject>

class QxtWebCommunicator : public QObject
	{
	Q_OBJECT

	public:
		QxtWebCommunicator(QObject * parent=0);

		void receive(QTcpSocket *);
		void send(QString);
	};

