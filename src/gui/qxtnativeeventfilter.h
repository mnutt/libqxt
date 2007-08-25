/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
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
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/
#ifndef QXTNATIVEEVENTFILTER_H
#define QXTNATIVEEVENTFILTER_H

#include "qxtapplication.h"

typedef struct tagMSG MSG;
typedef union  _XEvent XEvent;
typedef struct OpaqueEventRef *EventRef;
typedef struct OpaqueEventHandlerCallRef *EventHandlerCallRef;

class QxtNativeEventFilter
{
public:
	virtual ~QxtNativeEventFilter()
	{ qxtApp->removeNativeEventFilter(this); }

	virtual bool x11EventFilter(XEvent* event) = 0;
	virtual bool winEventFilter(MSG* msg, long* result) = 0;
    virtual bool macEventFilter(EventHandlerCallRef caller, EventRef event) = 0;
};

#endif // QXTNATIVEEVENTFILTER_H
