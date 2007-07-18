/****************************************************************************
**
** Copyright (C) J-P Nurmi <jpnurmi@gmail.com>. Some rights reserved.
**
** This file is part of the QxtGui module of the
** Qt eXTension library <http://libqxt.sourceforge.net>
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef QXTGROUPBOXPLUGIN_H
#define QXTGROUPBOXPLUGIN_H

#include <QObject>
#include "qxtdesignerplugin.h"

class QxtGroupBoxPlugin : public QObject, public QxtDesignerPlugin
{
	Q_OBJECT
	
public:
	QxtGroupBoxPlugin(QObject* parent = 0);
	
	QWidget* createWidget(QWidget* parent);
	QString domXml() const;
	bool isContainer() const { return true; }
};

#endif // QXTGROUPBOXPLUGIN_H
