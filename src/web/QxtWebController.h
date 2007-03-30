#ifndef QXTWEBCONTROLLER_HEADasdasdEGUARD
#define QXTWEBCONTROLLER_HEADasdasdEGUARD

#include <QObject>
#include <QStringList>
#include <QTextStream>
#include <QHash>


#define  STATUS_OK { document() << "Status: 200 OK\r\n"; document() << "Content-Type: text/html\r\n\r\n";  }


class QxtHtmlTemplate;
class QxtWebController : public QObject 
	{
	Q_OBJECT
	public:
		QxtWebController(QObject* parent, QString objectName=QString());
		void push(QHash<QByteArray, QByteArray>,QHash<QByteArray, QString> , QxtHtmlTemplate  *,QTextStream *);

	protected:
		QHash<QByteArray, QString>    POST;
		QHash<QByteArray, QByteArray> SERVER;


		QTextStream & document();
		void assign(QString key, QString value);

	public slots:
		int index();



	private: ///TODO: hide
		QxtHtmlTemplate  * view;
		QTextStream * stream;
	};

#endif

