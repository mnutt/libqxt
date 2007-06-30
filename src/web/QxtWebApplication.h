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

#ifndef QXTWEBAPPLICATION_HEADER_GIAURX_H
#define QXTWEBAPPLICATION_HEADER_GIAURX_H

#include <QObject>
#include <QxtError.h>
#include <QxtPimpl.h>
#include <QHostAddress>

class QxtWebApplicationPrivate;
class QxtWebApplication : public QObject
	{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtWebApplication);
	public:
		QxtWebApplication(void (*callback)(QObject *),QObject * parent=0);
		QxtError listen(const QHostAddress & address = QHostAddress::Any, quint16 port = 8000);
	};




#endif

