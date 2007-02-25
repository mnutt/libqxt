#include <QApplication>
#include <QTimer>
#include <QLabel>

#include "thread.h"
#include <QxtKit/QxtEventThread>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QTimer t;
	QxtEventThread<thread> f;
	f.start();


	qDebug()<<"signal in Thread "<<QThread::currentThreadId ();
	f.connect(&t,SIGNAL(timeout()),SLOT(call()));
	t.start(200);


	app.exec();
}
