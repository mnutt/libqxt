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
#ifndef QxtWebCommunicatorHEaderCrappasljdnsaidnasd
#define QxtWebCommunicatorHEaderCrappasljdnsaidnasd



#include <QObject>
#include <QHash>
#include <QTextStream>
#include <QMutex>

class QTcpSocket;


class QxtWebCommunicator : public QObject
	{
	Q_OBJECT

	public:
		QxtWebCommunicator(QObject * parent);

		void initAfterCreate();


		void incoming(QTcpSocket * tcpSocket,QHash<QByteArray,QByteArray> SERVER);


	public slots:
		void update();


	private:
		QTcpSocket * holdsocket;


		QHash<QByteArray,QByteArray> tracelist;


		QMutex mutex;

	};



#endif

