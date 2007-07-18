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


#ifndef QXTTREEWIDGETITEM_H
#define QXTTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "qxtnamespace.h"
#include "qxtglobal.h"

class QXT_GUI_EXPORT QxtTreeWidgetItem : public QTreeWidgetItem
{
public:
	explicit QxtTreeWidgetItem(int type = Type);
	QxtTreeWidgetItem(const QStringList& strings, int type = Type);
	QxtTreeWidgetItem(QTreeWidget* parent, int type = Type);
	QxtTreeWidgetItem(QTreeWidget* parent, const QStringList& strings, int type = Type);
	QxtTreeWidgetItem(QTreeWidget* parent, QTreeWidgetItem* preceding, int type = Type);
	QxtTreeWidgetItem(QTreeWidgetItem* parent, int type = Type);
	QxtTreeWidgetItem(QTreeWidgetItem* parent, const QStringList& strings, int type = Type);
	QxtTreeWidgetItem(QTreeWidgetItem* parent, QTreeWidgetItem* preceding, int type = Type);
	QxtTreeWidgetItem(const QxtTreeWidgetItem& other);
	virtual ~QxtTreeWidgetItem();
	
#ifndef QXT_DOXYGEN_RUN
	virtual void setData(int column, int role, const QVariant& value);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTTREEWIDGET_H
