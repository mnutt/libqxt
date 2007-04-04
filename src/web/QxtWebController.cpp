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
#include "QxtWebController.h"
#include "QxtWebApplication_p.h"
#include "QxtWebInternal.h"
#include "QxtHtmlTemplate.h"




/*!
    \class QxtWebController QxtWebController
    \ingroup web
    \brief The part of QxtWeb where your buisness logic code goes


	The controllers name is determinated via qts objectName.
	reimplement this and add actions you want .\n

	An Action is a public slot that gets called when a request includes an action.\n


	<pre>
	http: //domain/controller/<b>action</b>
	</pre>

	\n
	in your implementation: \n

	<pre>
	public slots:
		int <b>action</b>()
			{
			return 0;
			}
	</pre>
	


	a request without action goes to the index action. Don't forget to implement it.\n


	if you want the arguments to the request to be passed to your funtion, define them too
	
	<pre>
	http: //domain/controller/action/<b>helloWorld</b>
	</pre>

	\n
	in your implementation: \n
	
	\code
		int action(QString parameter1)
			{
			parameter1=="helloWorld"
			return 0;
			}
	\endcode


	you can use an integer too, or whatever QVariant can be converted too.\n
	In case you want a "catch all parameters" function, use a QStringList.

	\n

	\n \n

	<h3>there are 3 ways to comunicate with the browser:</h3> \n \n

		<h4>the propably best way</h4> is to use the MVC aproach and call assign(key,vale) then let the view render the html by returning a positive value. \n

		\code
			int action()
				{
				assign("text","hello world");
				return 0;
				}
		\endcode
		
		the MVC automagic will search for the view fitting your action. this is (depending on your settings):  ./app/view/controller/action.html and fill all ocurances of "<?=text?>" with "hello world". The syntax is based on php and will be extended with QScript as soon as it is released. \n \n \n

		<h4>the second way</h4> is to write the html directly to the stream and return a negative value. \n In this case no view is rendered. You will need to write the respone header too. if you just want a simple "200 FOUND" header, the standard one, you can use QXT_WEB_200.

		\code
			int action()
				{
				QXT_WEB_200
				document()<<"hello world";
				return -1;
				}
		\endcode

		\n \n \n
		
		<h4>the third way</h4> is to use a different view then the proposed one.

		\code
			int action()
				{
				QXT_WEB_200
				QxtHtmlTemplate view;
				view.open("./app/view/controller/myotherview.html");
				view.assign("text","hello world");
				document()<<view.render();
				return -2;
				}
		\endcode

		

 */


QxtWebController::QxtWebController(QObject* parent,QString objectName_c):QObject(parent)
	{
	if (!objectName_c.isEmpty())
		setObjectName(objectName_c);

	view=0;
	}

int QxtWebController::index()
	{
	QxtWebInternal::internalPage(404,
		
		"You are seeing this page becouse someone forgot to reimplement the index function of this Controller. (\""+objectName()+"\")<br/>"
		,document(),0,
		"When you inherit from QxtWebController, this is the minimal code: "
		"<small><pre>"		
		+QxtWebInternal::toHtml("#include <QxtWebController>")+"<br/>"
		
		+QxtWebInternal::toHtml("class "+objectName()+"Controller : public  QxtWebController { ")+"<br/>"
		+"Q_OBJECT<br/>"
		+"public:<br/>"
		+"<br/>    "
		+QxtWebInternal::toHtml(objectName()+"Controller(QObject* parent):QxtWebController(parent,\""+objectName()+"\"){}")+"<br/>"
		+"<br/>"
		+QxtWebInternal::toHtml("    int QxtWebController::index()")+"<br/>"
		+QxtWebInternal::toHtml("            {return 0;}")+"<br/>"
		+QxtWebInternal::toHtml("}")+"<br/>"
		+"</pre></small><br/>"


		);


	return -1;
	}


void QxtWebController::push( QHash<QByteArray, QByteArray> server,QHash<QString, QString>  post, QxtHtmlTemplate  *v,QTextStream * s )
	{
	view = v;
	stream=s;
	POST=post;
	SERVER=server;
	}

QTextStream & QxtWebController::document()
	{
	return *stream;
	}

void QxtWebController::assign(QString key, QString value)
	{
	if (!view)
		{
		qWarning("QxtWebController::assign can only be called within a web slot");
		return;
		}
	view->assign(key,value);
	}

