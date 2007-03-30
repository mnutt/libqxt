#include <QCoreApplication>
#include <QxtError>


#include <QxtWebApplication>
#include <QxtWebController>
#include "testcontroller.h"




void webmain(QObject * worker)
	{
	new QxtWebController(worker,"root");
	new QxtWebController(worker,"post");
	new InfoController (worker);
	}


int main(int argc, char *argv[])
	{
	QCoreApplication app(argc, argv);
	QxtWebApplication server(&webmain);
	

	QXT_DROP_SCOPE(error,server.listen(QHostAddress::Any,4000)) 
		{
		qDebug("Unable to start the server: %s.",error.errorString());
		return 0;
		}

	return app.exec();
	}


