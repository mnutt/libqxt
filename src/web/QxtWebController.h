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
#ifndef QXTWEBCONTROLLER_HEADERGUARD
#define QXTWEBCONTROLLER_HEADERGUARD

#include <QObject>
#include <QStringList>
#include <QTextStream>
#include <QHash>

#include <QxtCore/QxtPimpl>


#define  QXT_WEB_200 { document() << "Status: 200 OK\r\n"; document() << "Content-Type: text/html\r\n\r\n";  }


class QxtHtmlTemplate;
class QxtWebController : public QObject 
	{
	Q_OBJECT

	public:
		QxtWebController(QObject* parent, QString objectName=QString());

	protected:

		QHash<QString, QString>    POST;
		QHash<QByteArray, QByteArray> SERVER;

		QTextStream & document();
		void assign(QString key, QString value);

	friend class QxtWebApplicationWorker;

	private slots:
		int index();

	private:
		void push(QHash<QByteArray, QByteArray>,QHash<QString, QString> , QxtHtmlTemplate  *,QTextStream *);

		QxtHtmlTemplate  * view;
		QTextStream * stream;
	};

#endif

