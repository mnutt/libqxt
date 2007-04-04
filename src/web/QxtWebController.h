#ifndef QXTWEBCONTROLLER_HEADERGUARD
#define QXTWEBCONTROLLER_HEADERGUARD

#include <QObject>
#include <QStringList>
#include <QTextStream>
#include <QHash>

#include <QxtCore/QxtPimpl>


#define  QXT_WEB_200 { document() << "Status: 200 OK\r\n"; document() << "Content-Type: text/html\r\n\r\n";  }


class QxtHtmlTemplate;
class QxtWebController : public QObject 
	{
	Q_OBJECT

	public:
		QxtWebController(QObject* parent, QString objectName=QString());

	protected:

		QHash<QString, QString>    POST;
		QHash<QByteArray, QByteArray> SERVER;

		QTextStream & document();
		void assign(QString key, QString value);

	friend class QxtWebApplicationWorker;

	private slots:
		int index();

	private:
		void push(QHash<QByteArray, QByteArray>,QHash<QString, QString> , QxtHtmlTemplate  *,QTextStream *);

		QxtHtmlTemplate  * view;
		QTextStream * stream;
	};

#endif

