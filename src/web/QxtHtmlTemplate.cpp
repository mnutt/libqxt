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

#include "QxtHtmlTemplate.h"
#include <QFile>

QxtHtmlTemplate::QxtHtmlTemplate(QObject* 
parent) : QObject(parent) 
	{
	}


bool QxtHtmlTemplate::open(const QString& filename)
	{
	QFile f(filename);
	f.open(QIODevice::ReadOnly);
	data = f.readAll();
	f.close();
	if (data.isEmpty())return false;
	return true;
	}


void QxtHtmlTemplate::assign(QString key, QString value) 
	{
	vars[key] = value.replace("\\", "\\\\").replace("{", "\\{");
	}

QString QxtHtmlTemplate::render() const 
	{
	QString output = data;
	foreach(QString key, vars.keys()) 
		{
		output = output.replace("<?="+key+"?>", vars[key]);
		}
	return output;
	}

void QxtHtmlTemplate::clear()
        {
        vars.clear();
        }
