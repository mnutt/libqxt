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
#ifndef QXTMETAOBJECT_H
#define QXTMETAOBJECT_H

#include <QMetaObject>
#include <QGenericArgument>
class QByteArray;
class QxtBoundFunction;
class QxtBoundArgument;

namespace QxtMetaObject
{
	QByteArray methodName(const char* method);
    QxtBoundFunction* bind(QObject* recv, const char* invokable,
                           QGenericArgument p1 = QGenericArgument(),
                           QGenericArgument p2 = QGenericArgument(),
                           QGenericArgument p3 = QGenericArgument(),
                           QGenericArgument p4 = QGenericArgument(),
                           QGenericArgument p5 = QGenericArgument(),
                           QGenericArgument p6 = QGenericArgument(),
                           QGenericArgument p7 = QGenericArgument(),
                           QGenericArgument p8 = QGenericArgument(),
                           QGenericArgument p9 = QGenericArgument(),
                           QGenericArgument p10 = QGenericArgument());
    bool connect(QObject* sender, const char* signal, QxtBoundFunction* slot,
                 Qt::ConnectionType type = Qt::AutoConnection);
}

#define QXT_BIND(i) QGenericArgument("QxtBoundArgument", reinterpret_cast<void*>(i))

#endif // QXTMETAOBJECT_H
