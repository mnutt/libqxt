#include "QxtEventThread.h"
using namespace QxtInternal;

void QxtThreadConnectionSender::connect( const QObject * sender, const char * signal, const char * method )
	{
	emit(connect_si(sender,signal,method ));
	}



QxtThreadConnector::QxtThreadConnector(QObject * t,QxtThreadConnectionSender * csender):QObject()
	{
	t_t=t;
	QObject::connect(csender, SIGNAL(connect_si( const QObject * , const char * , const char *  )),this, SLOT(connect_sl( const QObject * , const char * , const char *  )),Qt::QueuedConnection);
	}


void QxtThreadConnector::connect_sl( const QObject * sender, const char * signal, const char * method )
	{
	QObject::connect(sender,signal, t_t,method,Qt::QueuedConnection);
	}





/*!
\class QxtEventThread QxtEventThread
\ingroup kit
\brief QObject which can have slots running in a different Thread

this provides you with the clasic QThread + QObject as receiver  solution all in one.\n
signals connected with QxtEventThread::connect are executing the slot in a different Thread.
for implementation reasons you need to call start() before connect().

\warning slots connected to with anything else then QxtEventThread::connect will execute in the main thread.

\n
\n

usage:
\code
QxtEventThread<MyObject> eventthread;
eventthread.start();
eventthread.connect(timer,SIGNAL(timout()),SLOT(myslot()));
\endcode





*/


QxtEventThreadPrivate::QxtEventThreadPrivate(QObject *parent):QThread(parent)
	{
	csender = new QxtInternal::QxtThreadConnectionSender();
	}

QxtEventThreadPrivate::~QxtEventThreadPrivate()
	{
	exit();
	}

/**connect a signal to the threads slot
use this just like you would use the global connect macro. just ommit the sender
*/
void QxtEventThreadPrivate::connect ( const QObject * sender, const char * signal, const char * method ) const
	{
	if(!instance()){msleep (10);}
	if(!instance()){qWarning("QxtEventThread: can only connect to a running instance");return;}
	csender->connect(sender,signal,method);
	}

void QxtEventThreadPrivate::start ( Priority priority  )
	{
	QThread::start(priority);
	}

void  QxtEventThreadPrivate::run()
	{
	QxtInternal::QxtThreadConnector c(instance(),csender);
	connector=&c;

	exec();
	delete instance();
	}
