#include <QxtScgiApplication.h>
#include <QxtScgiController.h>

class test : public QxtScgiController
        {
        Q_OBJECT
        public:
                test(QxtScgiApplication *parent):QxtScgiController("root",parent)
			{
			}

	public slots:

		 int index()
                        {
			echo()<<"Status: 200 OK\r\nContent-Type: text/html\r\n\r\n";
			echo()<<"foo";
                        return 0;
                        }
		 int index(QString a, QString b=QString("default"), QString c=QString("default2"))
                        {
			echo()<<"Status: 200 OK\r\nContent-Type: text/html\r\n\r\n";
			echo()<<"a: "<<a<<"<br/> b: "<<b<<"<br/> c: "<<c;
                        return 0;
                        }

        };

int main(int argc, char *argv[])
	{
	QxtScgiApplication app(argc, argv);
	test t(&app);
	QxtScgiController e("error",&app);

	return app.exec(4000);
	}


#include "main.moc"
