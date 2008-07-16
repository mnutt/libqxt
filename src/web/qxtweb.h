/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtWeb module of the Qxt library.
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtabstracthttpconnector.h"
#include "qxtabstractwebservice.h"
#include "qxtabstractwebsessionmanager.h"
#include "qxthtmltemplate.h"
#include "qxthttpsessionmanager.h"
#include "qxtmail.h"
#include "qxtsendmail.h"
#include "qxtwebcontent.h"
#include "qxtwebevent.h"
#include "qxtwebservicedirectory.h"
#include "qxtwebslotservice.h"

/**
\defgroup QxtWeb QxtWeb
\brief    The QxtWeb module provides tools for creating web services using Qt.

QxtWeb provides tools for creating event-driven web services using Qt.

The general usage pattern is as follows:

\li Create a QxtAbstractWebSessionManager object, such as QxtHttpSessionManager, for each protocol that can interface to the service.
\li If using QxtHttpSessionManager, select a connector plugin, such as QxtHttpServerConnector.
\li Register a QxtAbstractWebService factory. The factory is invoked each time a new session is created and returns a service object
    for that session. QxtWebServiceDirectory allows you to register multiple services and selects between them based on the path.
\li Invoke QxtAbstractWebSessionManager::start() to begin accepting connections.

When a new visitor connects who does not belong to a session, a new service instance is created. When a request is received, a
QxtAbstractWebService::pageRequestedEvent() is dispatched to the service. When the service is ready to respond to the request, it posts
a QxtWebPageEvent to the session manager. This is done asynchronously; there is no requirement that the pageRequestedEvent handler
must respond to the request before the function ends, but such a response must eventually be posted or the web browser will eventually
time out.
*/
