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
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/


#include <QThread>

#include <Qxt/qxtglobal.h>
namespace QxtInternal{
class QxtThreadConnectionSender : public QObject
	{
	Q_OBJECT
	public:

		void connect( const QObject * sender, const char * signal, const char * method );
	signals:
		void connect_si( const QObject * sender, const char * signal, const char * method );
	};


class QxtThreadConnector : public QObject
	{
	Q_OBJECT
	public:
		QxtThreadConnector(QObject * t,QxtThreadConnectionSender * csender);

	private slots:
		void connect_sl( const QObject * sender, const char * signal, const char * method );

	private:
		QObject * t_t;
	};



class QxtEventThreadPrivate : public QThread
	{
	public:

		QxtEventThreadPrivate(QObject *parent=0);

		~QxtEventThreadPrivate();

		void connect ( const QObject * sender, const char * signal, const char * method ) const;

		void run();

		QxtInternal::QxtThreadConnector * connector;
		QxtInternal::QxtThreadConnectionSender * csender;

		virtual QObject * instance()const =0;


	};

}




template<typename T>
class QXT_KIT_EXPORT QxtEventThread : public QxtInternal::QxtEventThreadPrivate
	{
	public:
	QxtEventThread(QObject *parent=0):QxtEventThreadPrivate(parent)
		{
		instance_p=NULL;
		}

	QObject * instance() const {return instance_p;}

	void  run()
		{
 		T t;
 		instance_p = &t;
		QxtEventThreadPrivate::run();
		}

	T * instance_p;
	};
