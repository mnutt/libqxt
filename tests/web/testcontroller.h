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



#include <QxtWebWidget>
#include <QxtHtmlTemplate>
#include <QTimer>


class InfoController : public QxtWebWidget
	{
	Q_OBJECT
	public:
 		InfoController(QObject* parent);
	public slots:
		int click();
		int index();
	protected:
		virtual void paintEvent(QTextStream & stream);
	private slots:
		void sec1();
		void sec2();
		void sec3();
		void sec4();
	private:
		QxtHtmlTemplate view;
	};








		/*
		int test()
			{
			QByteArray server;
			QHashIterator<QByteArray, QByteArray> ii(SERVER);
 			while (ii.hasNext()) 
				{
				ii.next();
				server+="<tr><td>";
				server+=ii.key();
				server+="</td><td>";
				server+=ii.value();
				server+="</td></tr>\r\n";
				}

	
			QByteArray post;
			QHashIterator<QString, QString> ii2(POST);
			while (ii2.hasNext()) 
				{
				ii2.next();
				post+="<tr><td>";
				post+=ii2.key();
				post+="</td><td><pre>";
				post+=ii2.value().toUtf8();
				post+="</pre></td></tr>\r\n";
				}
	
			assign("url",SERVER["REQUEST_URI"]);
			assign("post",post);
			assign("server",server);
			return 0;
			}
		*/

