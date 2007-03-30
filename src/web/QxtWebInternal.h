#include <QString>
#include <QHash>

class QTcpSocket;
class QTextStream;
class QxtWebInternal
	{
	public:
		static void internalPage (int code,QString description,QTcpSocket *, QHash<QByteArray, QByteArray>  * SERVER=0,QString hint=QString());
		static void internalPage (int code,QString description,QTextStream &  stream, QHash<QByteArray, QByteArray>  * SERVER=0,QString hint=QString());
		static QString toHtml (QString text);
		static QString WebRoot();

	private:
		static bool internalPage_p (int code,QString description,QTextStream &  stream, QHash<QByteArray, QByteArray>  * SERVER=0,QString hint=QString());
	};



