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
			echo()<<"Status: 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n";
			echo()<<"foo";
                        return 0;
                        }
		 int index(QString a, QString b=QString("default"), QString c=QString("default2"))
                        {
			echo()<<"Status: 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n";
			echo()<<"a: "<<a<<"<br/> b: "<<b<<"<br/> c: "<<c;
                        return 0;
                        }

        };

class err : public QxtScgiController
        {
        Q_OBJECT
        public:
                err(QxtScgiApplication *parent):QxtScgiController("error",parent)
			{
			}

	public slots:

		 int index(QString a=QString("500"),QString b=QString(),QString c=QString(),QString d=QString(),
			QString e=QString(),QString f=QString(),QString g=QString())
                        {
			echo()<<"Status: 404 NOT FOUND\r\nContent-Type: text/html; charset=utf-8\r\n\r\n";
			echo()<<"shits<br/>"
			"error "<<a<<"<br/>"
			<<b<<"<br/>"
			<<c<<"<br/>"
			<<d<<"<br/>"
			<<e<<"<br/>"
			<<f<<"<br/>"
			<<g<<"<br/>";
                        return 0;
                        }

        };





int main(int argc, char *argv[])
	{
	QxtScgiApplication app(argc, argv);
	test t(&app);
	err e(&app);
	return app.exec(4000);
	}


#include "main.moc"
