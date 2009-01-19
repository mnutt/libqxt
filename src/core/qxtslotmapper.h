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
#ifndef QXTSLOTMAPPER_H
#define QXTSLOTMAPPER_H

#include <QObject>
#include <qxtpimpl.h>
#include <qxtglobal.h>

class QxtSlotMapperPrivate;

class QXT_CORE_EXPORT QxtSlotMapper : public QObject
{
    QXT_DECLARE_PRIVATE(QxtSlotMapper);
	
public:
    explicit QxtSlotMapper(QObject* parent = 0);
    ~QxtSlotMapper();

    void addMapping(const QVariant& parameter, QObject* receiver, const char* member);
    void removeMapping(const QVariant& parameter, QObject* receiver = 0, const char* member = 0);

    bool connect(const QObject* sender, const char* signal);

    int qt_metacall(QMetaObject::Call call, int id, void** arguments);
};

#endif // QXTSLOTMAPPER_H
