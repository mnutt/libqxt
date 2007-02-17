/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtTreeWidgetItem.h"
#include "QxtTreeWidget.h"

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
