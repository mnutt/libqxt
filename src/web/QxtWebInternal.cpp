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

#include "QxtWebInternal.h"
#include "QxtWebApplication_p.h"
#include "QxtHtmlTemplate.h"
#include <QUrl>


static QString WebRoot_m="./app";



QString QxtWebInternal::WebRoot()
	{
	return WebRoot_m;
	}



//---------------------------------------------------------------------------

void QxtWebInternal::internalPage (int code,QString text, QTcpSocket * socket, servertype * SERVER,QString hint)
	{
	QTextStream  stream (socket);

	if (!QxtWebInternal::internalPage_p(code,text,stream,SERVER,hint) )
		{
		stream<<"Status: 500 INTERNAL SERVER ERROR\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";
		stream<<"<h2>The Server was unable to display an internal Page</h2><br />\n";
		stream<<"for the code: " << code << "<br />\n";
		stream<<"with aditional info: " << text << "<br />\n";
		stream<<"Please report this to the site admin\n";
		}


	stream.flush ();
	socket->disconnectFromHost();
	socket->waitForDisconnected();
	socket->deleteLater();
	}


//---------------------------------------------------------------------------


void QxtWebInternal::internalPage (int code,QString text,QTextStream &  stream, servertype * SERVER,QString hint)
	{
	if (!QxtWebInternal::internalPage_p(code,text,stream,SERVER,hint) )
		{
		stream<<"Status: 500 INTERNAL SERVER ERROR\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";
		stream<<"<h2>The Server was unable to display an internal Page</h2><br />\n";
		stream<<"for the code: " << code << "<br />\n";
		stream<<"with aditional info: " << text << "<br />\n";
		stream<<"This can happen when internal views are missing or corupt.<br />\n";
		stream<<"Please report this to the site admin\n";
		}
	stream.flush ();
	}


//---------------------------------------------------------------------------


bool QxtWebInternal::internalPage_p (int code,QString description, QTextStream &  stream, servertype * SERVER,QString hint)
	{
	if (code == 12345)
		{
		QxtHtmlTemplate  t;
		if (!t.open(WebRoot_m+"/internal/mint.html"))return false;

		stream<<"Status: 200 OK\r\n";
		stream<<"Content-Type: text/html\r\n";
 		stream<<"Set-Cookie: mint="<<description<<"; path=/;\r\n";
		stream<<"\r\n\r\n";

		///TODO  when there are no cookies available, we end in recursive page loads


		if (SERVER)t.assign("url",(*SERVER)["REQUEST_URI"]);
		stream<<t.render();
		}

	else if (code == 404)
		{
		QxtHtmlTemplate  t;
		if (!t.open(WebRoot_m+"/internal/404.html"))return false;

		stream<<"Status: 404 NOT FOUND\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";



		t.assign("description",description);
		t.assign("hint",hint);

		if (SERVER)t.assign("url",(*SERVER)["REQUEST_URI"]);
		stream<<t.render();
		}

	else if (code == 4041)
		{
		QxtHtmlTemplate  t;
		if (!t.open(WebRoot_m+"/internal/404.html"))return false;

		stream<<"Status: 404 NOT FOUND\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";

		t.assign("description","The Controller \""+description+"\" could not be found!<br>");

		t.assign("hint",
			"In your QxtWebApplication  creator callback do the following to add it:"
			"<small><pre>"
			+QxtWebInternal::toHtml("#include <QxtWebController>")+"<br/>"
		
			+QxtWebInternal::toHtml("void webmain(QObject * worker) ")+"<br/>"
			+QxtWebInternal::toHtml(" {")+"<br/>"
			+QxtWebInternal::toHtml(" new QxtWebController(worker,\"" +description+ "\");")+"<br/>"
			+QxtWebInternal::toHtml(" }")+"<br/>"
			+"</pre></small><br/>"

			);

		if (SERVER)t.assign("url",(*SERVER)["REQUEST_URI"]);
		stream<<t.render();
		}


	else if (code == 4042)
		{
		QxtHtmlTemplate  t;
		if (!t.open(WebRoot_m+"/internal/404.html"))return false;

		stream<<"Status: 404 NOT FOUND\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";
							 
		t.assign("description","The action \""+description+ "\" could not be found in the  \""+hint+"\" controller!<br>");

		t.assign("hint",
			"To add the minimal action to your Controller add a slot like this:"
			"<small><pre>"
			+QxtWebInternal::toHtml("public slots:")+"<br/>"
			+QxtWebInternal::toHtml("  int "+description+"() ")+"<br/>"
			+QxtWebInternal::toHtml("      /{return 0;}")	+"<br/>"
			+"</pre></small><br/>"
			);

		if (SERVER)t.assign("url",(*SERVER)["REQUEST_URI"]);
		stream<<t.render();
		}

	else if (code == 4043)
		{
		QxtHtmlTemplate  t;
		if (!t.open(WebRoot_m+"/internal/404.html"))return false;

		stream<<"Status: 404 NOT FOUND\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";
							 
		t.assign("description","Missing view \""+description+ "\" (for the  \""+hint+"\" controller) !<br>");

		t.assign("hint",
			"Create a html file "+WebRoot_m+ "/view/"+hint+ "/"+description+".html"
			);

		if (SERVER)t.assign("url",(*SERVER)["REQUEST_URI"]);
		stream<<t.render();
		}

	else if (code == 4046)
		{
		QxtHtmlTemplate  t;
		if (!t.open(WebRoot_m+"/internal/404.html"))return false;

		stream<<"Status: 404 NOT FOUND\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";
							 
		t.assign("description","Invalid flector call \""+description+ "\" !<br>");

		t.assign("hint",
			"Somehow a request asks for an invalid flektor, or calls the flector with too less arguments. Try to Correct that."
			);

		if (SERVER)t.assign("url",(*SERVER)["REQUEST_URI"]);
		stream<<t.render();
		}

	else if (code == 5011)
		{
		QxtHtmlTemplate  t;
		if (!t.open(WebRoot_m+"/internal/505.html"))
			if (!t.open(WebRoot_m+"/internal/error.html"))
				return false;

		stream<<"Status: 501 Not Implemented\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";
				

		t.assign("code","501");
			 
		t.assign("description","The asynchronous action you requested requires a communicator.");

		t.assign("hint",
			"In your QxtWebApplication  creator callback do the following to add it:"
			"<small><pre>"
			+QxtWebInternal::toHtml("#include <QxtWebCommunicator>")+"<br/>"
		
			+QxtWebInternal::toHtml("void webmain(QObject * worker) ")+"<br/>"
			+QxtWebInternal::toHtml(" {")+"<br/>"
			+QxtWebInternal::toHtml(" new QxtWebCommunicator(worker);")+"<br/>"
			+QxtWebInternal::toHtml(" }")+"<br/>"
			+"</pre></small><br/>"
			);

		stream<<t.render();
		}
	else if (code == 204)
		{
		stream<<"Status: 205 Reset Content\r\n";
		stream<<"Content-Type: text/html\r\n\r\n";
		}
	else 
		{
		QxtHtmlTemplate  t;
		if (!t.open(WebRoot_m+"/internal/error.html"))return false;

		stream<<"Status: "<<code<<"\r\n";
		stream<<"Content-Type: text/html\r\n";
		stream<<"\r\n\r\n";

		t.assign("code",QString::number(code));

		t.assign("description",description);
		t.assign("hint",hint);
		stream<<t.render();
		}

	return true;
	}

//---------------------------------------------------------------------------

 QString QxtWebInternal::toHtml (QString text)
	{
	
	text.replace("&","&amp;");

	text.replace("\"","&quot;");
	text.replace("/","&frasl;");
	text.replace("<","&lt;");
	text.replace(">","&gt;");

	text.replace("{","&#123;");
	text.replace("}","&#125;");
	return text;
	}

//---------------------------------------------------------------------------

bool  QxtWebInternal::readScgiHeaderFromSocket(QTcpSocket * tcpSocket, QHash<QByteArray, QByteArray> & SERVER)
	{
	if (!tcpSocket)return false;


	///--------------get the header size----------------
	
	QByteArray size_in;
	while(!size_in.endsWith(':'))
		{
		if(!tcpSocket->bytesAvailable ())
			if (!tcpSocket->waitForReadyRead (200))
				{internalPage(408,"Timeout while waiting for request data.",tcpSocket); return false;}

		char a[4]; ///4? yes, i know i'm paranoid about bounds.


		if (!tcpSocket->read (a, 1 ))
			{internalPage(500,"Socket I/O failure.",tcpSocket); return false;}

		size_in+=a[0];

		if (size_in.size()>20)/// after the 20ths char is an attack atemp for sure
			{internalPage(400,"The Overflow Protector has been triggered.",tcpSocket); return false;}

		}
	

	size_in.chop(1);
	int size=size_in.toInt()+1;


	if (size>10240)  ///do not accept headers over 10kb
		{internalPage(411,"Your Header was too long.",tcpSocket); return false;}


	///--------------read the header------------------

	while(tcpSocket->bytesAvailable ()<size)
		{
		if (!tcpSocket->waitForReadyRead (200))
			{internalPage(408,"Timeout while waiting for request data.",tcpSocket); return false;}
		}
	QByteArray header_in;
	header_in.resize(size);

	if (tcpSocket->read (header_in.data(), size )!=size)
		{ internalPage(500,"Socket I/O failure.",tcpSocket); return false;}

	if (!header_in.endsWith(','))
		{internalPage(501,"The Post method you tried is not supported.",tcpSocket);return false;}
	///--------------parse the header------------------


	int i=0;
	QByteArray name="";
	QByteArray a =header_in;
	while((i=a.indexOf('\0'))>-1)
		{
		if(name=="")
			{
			name= a.left(i).replace('\0',"");
			}
		else
			{
			SERVER[name]=a.left(i).replace('\0',"");
			name="";
			}
		
		a=a.mid(i+1);
		}


	return true;
	}
//---------------------------------------------------------------------------

bool QxtWebInternal::readScgiContentFromSocket(QTcpSocket * tcpSocket,int content_size, QString contentType ,QHash<QString,QString> & POST)
	{
	if (!tcpSocket)return false;

	if (!content_size)
		{
		return true;
		}


	///--------------read the content------------------

	while(tcpSocket->bytesAvailable ()<content_size)
		{
		if (!tcpSocket->waitForReadyRead (10000))
			{
			QxtWebInternal::internalPage(408,"Timeout while waiting for request data.",tcpSocket);
			return false;
			}
		}
	
	QByteArray content_in;
	content_in.resize(content_size);


	if (tcpSocket->read (content_in.data(), content_size )!=content_size)
		{
		QxtWebInternal::internalPage(500,"Socket I/O failure.",tcpSocket);
		return false;
		}

	
	if (contentType!="application/x-www-form-urlencoded")
		{
		QxtWebInternal::internalPage(501,"The Post method you tried is not supported.",tcpSocket);
		return false;
		}


	QList<QByteArray> posts = content_in.split('&');


	QByteArray post;
	foreach(post,posts)
		{
		QList<QByteArray> b =post.split('=');
		if (b.count()!=2)continue;

		

		POST[QUrl::fromPercentEncoding  ( b[0].replace("+","%20"))]=QUrl::fromPercentEncoding  ( b[1].replace("+","%20") );
		}




	
	return true;

	}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

