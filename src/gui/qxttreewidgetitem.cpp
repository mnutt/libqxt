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


#include "qxttreewidgetitem.h"
#include "qxttreewidget.h"

/*!
    \class QxtTreeWidgetItem QxtTreeWidgetItem
    \ingroup gui
    \brief An extended tree widget item.

    QxtTreeWidgetItem provides means for offering check state change signals.

    \sa QxtTreeWidget

    \note Requires Qt 4.2 or newer.
 */


QxtTreeWidgetItem::QxtTreeWidgetItem(int type)
	: QTreeWidgetItem(type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(const QStringList& strings, int type)
	: QTreeWidgetItem(strings, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidget* parent, int type)
	: QTreeWidgetItem(parent, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidget* parent, const QStringList& strings, int type)
	: QTreeWidgetItem(parent, strings, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidget* parent, QTreeWidgetItem* preceding, int type)
	: QTreeWidgetItem(parent, preceding, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidgetItem* parent, int type)
	: QTreeWidgetItem(parent, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidgetItem* parent, const QStringList& strings, int type)
	: QTreeWidgetItem(parent, strings, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(QTreeWidgetItem* parent, QTreeWidgetItem* preceding, int type)
	: QTreeWidgetItem(parent, preceding, type)
{
}

QxtTreeWidgetItem::QxtTreeWidgetItem(const QxtTreeWidgetItem& other)
	: QTreeWidgetItem(other)
{
}

QxtTreeWidgetItem::~QxtTreeWidgetItem()
{
}

void QxtTreeWidgetItem::setData(int column, int role, const QVariant& value)
{
	if (role == Qt::CheckStateRole)
	{
		const Qt::CheckState newState = static_cast<Qt::CheckState>(value.toInt());
		const Qt::CheckState oldState = static_cast<Qt::CheckState>(data(column, role).toInt());
		
		QTreeWidgetItem::setData(column, role, value);
		
		if (newState != oldState)
		{
			QxtTreeWidget* tree = qobject_cast<QxtTreeWidget*>(treeWidget());
			if (tree)
			{
				emit tree->itemCheckStateChanged(this);
			}
		}
	}
	else
	{
		QTreeWidgetItem::setData(column, role, value);
	}
}
