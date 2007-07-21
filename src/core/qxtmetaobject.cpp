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
#include "qxtmetaobject.h"

#include <QByteArray>
#include <QMetaObject>

namespace QxtMetaObject
{

/*!
    \fn QxtMetaObject::methodName()

    Returns the name of the given method.

    Example usage:
    \code
    QByteArray method = QxtMetaObject::methodName(" int foo ( int bar, double baz )");
    // method is now "foo"
    \endcode
 */
QByteArray methodName(const char* method)
{
	QByteArray name = QMetaObject::normalizedSignature(method);
	if (name.startsWith("1") || name.startsWith("2"))
		name = name.mid(1);
	const int idx = name.indexOf("(");
	if (idx != -1)
		name.truncate(idx);
	return name;
}

}
