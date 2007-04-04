#ifndef QXTWEBAPPLICATION_PRIVCATE_HEADER_GIAURX_H
#define QXTWEBAPPLICATION_PRIVCATE_HEADER_GIAURX_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QHash>
#include <QTextStream>
#include <QWaitCondition>
#include <QMutex>
#include <QMetaType>
#include <QTimer>

#include "QxtWebApplication.h"
#include "QxtWebCommunicator.h"



typedef  QHash<QByteArray, QByteArray> servertype;


class QxtHtmlTemplate;

Q_DECLARE_METATYPE(servertype)
Q_DECLARE_METATYPE(QxtHtmlTemplate  *)


//----------------------------------------------------------------------

class QxtWebApplicationThread : public QThread
	{
	Q_OBJECT
	
	public:
		QxtWebApplicationThread(void (*callback_m)(QObject *),QByteArray TID,QObject *parent);
		void run();

		///call this from outside. nonblocking (or at least not until everything has been startet up properly)
		void request(QTcpSocket *,servertype &SERVER);


		QByteArray mint(){return mint_m;}


	signals:
		void signal_request_to_worker(QTcpSocket *,servertype);


	private:
		QWaitCondition started;
		QMutex  started_m;
 		QTimer lifetime;
		
		QxtWebCommunicator * communicator;

		int lifetime_m;
		bool firstrun;
		QByteArray mint_m;
		void (*callback_m)(QObject *);
	};


//----------------------------------------------------------------------

class QxtWebApplicationPrivate : public QTcpServer,public QxtPrivate<QxtWebApplication>
	{
	Q_OBJECT
	QXT_DECLARE_PUBLIC(QxtWebApplication);

	public:
		QxtWebApplicationPrivate(QObject *parent = 0);
		void init(void (*callback)(QObject *));


	protected:
		void incomingConnection(int socketDescriptor);

	private slots:
		void threadfinished();


	private:
		QHash<QByteArray,QxtWebApplicationThread *>  mints;

		void (*callback_m)(QObject *);

	};


//----------------------------------------------------------------------

class QxtWebApplicationWorker : public QObject
	{
	Q_OBJECT
	public slots:		
		void execute_request(QTcpSocket * ,servertype );


	public:
		QxtWebApplicationWorker();


		QxtWebCommunicator * communicator;

		
		unsigned long requestDone;
	};


//----------------------------------------------------------------------


#endif


