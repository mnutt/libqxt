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
#include <QApplication>
#include <QTimer>
#include <QLabel>

#include "thread.h"
#include <QxtKit/QxtEventThread>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QTimer t;
	QxtEventThread<thread> f;
	f.start();


	qDebug()<<"signal in Thread "<<QThread::currentThreadId ();
	f.connect(&t,SIGNAL(timeout()),SLOT(call()));
	t.start(20);


	app.exec();
}
