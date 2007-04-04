/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/
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


