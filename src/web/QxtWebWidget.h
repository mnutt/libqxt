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

#ifndef QXTWEBWIDGET_HEADERGUARD
#define QXTWEBWIDGET_HEADERGUARD

#include <QObject>
#include <QStringList>
#include <QTextStream>
#include <QHash>
#include <QBuffer>

#include <QxtCore/QxtPimpl>


#define  QXT_WEB_200 { document() << "Status: 200 OK\r\n"; document() << "Content-Type: text/html\r\n\r\n";  }

class QTcpSocket;

class QxtWebWidget : public QObject 
	{
	Q_OBJECT

	public:
		QxtWebWidget(QObject* parent, QString objectName=QString());



	protected:
		virtual void paintEvent(QTextStream & stream);

		void clear();
		void assign(QString key, QString value);

	private slots:
		int index();


	friend class QxtWebApplicationWorker;

	private:
		void renderTo(QTcpSocket * tcpSocket);
	};

#endif

