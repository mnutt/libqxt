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

#include "QxtWebSession.h"

#include <QThread>
#include "QxtWebApplication_p.h"

/*!
	\class QxtWebSession QxtWebSession
	\ingroup web
	\brief an interface to the clients session worker

*/



/*!
\fn  
destroy a session thread after the current request has been handled.
*/
void QxtWebSession::destroy()
	{
	QxtWebApplicationThread * o= qobject_cast<QxtWebApplicationThread *>(QThread::currentThread ());

	if (!o)
		{
		qWarning("QxtWebSession::destroy() can only be called from inside a worker thread. e.g. from a controller.");
		return;
		}
	o->quit();
	}

