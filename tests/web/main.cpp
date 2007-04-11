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
#include <QCoreApplication>
#include <QxtError>


#include <QxtWebApplication>
#include <QxtWebWidget>
#include <QxtWebCommunicator>
#include "testcontroller.h"



void webmain(QObject * worker)
	{
 	new InfoController (worker);
	new QxtWebCommunicator(worker);
	}


int main(int argc, char *argv[])
	{
	QCoreApplication app(argc, argv);
	QxtWebApplication server(&webmain);
	

	QXT_DROP_SCOPE(error,server.listen(QHostAddress::Any,4000)) 
		{
		qDebug("Unable to start the server: %s.",error.errorString());
		return 0;
		}

	return app.exec();
	}


