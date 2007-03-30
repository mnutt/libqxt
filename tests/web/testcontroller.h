#include <QxtWebController>


class InfoController : public QxtWebController
	{
	Q_OBJECT
	public:
 		InfoController(QObject* parent):QxtWebController(parent,"info"){}

	public slots:
		int index()
			{
			assign("url",SERVER["REQUEST_URI"]);
			return 0;
			}

		int test()
			{
			QByteArray server;
			QHashIterator<QByteArray, QByteArray> ii(SERVER);
 			while (ii.hasNext()) 
				{
				ii.next();
				server+="<tr><td>";
				server+=ii.key();
				server+="</td><td>";
				server+=ii.value();
				server+="</td></tr>\r\n";
				}

	
			QByteArray post;
			QHashIterator<QByteArray, QString> ii2(POST);
			while (ii2.hasNext()) 
				{
				ii2.next();
				post+="<tr><td>";
				post+=ii2.key();
				post+="</td><td><pre>";
				post+=ii2.value().toUtf8();
				post+="</pre></td></tr>\r\n";
				}
	
			assign("url",SERVER["REQUEST_URI"]);
			assign("post",post);
			assign("server",server);
			return 0;
			}

		int NoSuchView()
			{
			return 0;
			}
	};



