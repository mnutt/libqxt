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
#include "qxttablewidgetitem.h"
#include "qxttablewidget.h"

/*!
    \class QxtTableWidgetItem QxtTableWidgetItem
    \ingroup gui
    \brief An extended QTableWidgetItem.

    QxtTableWidgetItem provides means for offering check state change signals and
    convenience methods for testing and setting flags.

    \sa QxtTableWidget
 */


QxtTableWidgetItem::QxtTableWidgetItem(int type)
	: QTableWidgetItem(type)
{
}

QxtTableWidgetItem::QxtTableWidgetItem(const QString& text, int type)
	: QTableWidgetItem(text, type)
{
}

QxtTableWidgetItem::QxtTableWidgetItem(const QIcon& icon, const QString& text, int type)
	: QTableWidgetItem(text, type)
{
	setIcon(icon); // for 4.1 compatibility
}

QxtTableWidgetItem::QxtTableWidgetItem(const QTableWidgetItem& other)
	: QTableWidgetItem(other)
{
}

QxtTableWidgetItem::~QxtTableWidgetItem()
{
}

/*!
    Returns \b true if the \a flag is set, otherwise \b false.

    \sa setFlag(), QTableWidgetItem::flags(), Qt::ItemFlag
 */
bool QxtTableWidgetItem::testFlag(Qt::ItemFlag flag) const
{
	return (flags() & flag);
}

/*!
    If \a enabled is \b true, the item \a flag is enabled; otherwise, it is disabled.

    \sa testFlag(), QTableWidgetItem::setFlags(), Qt::ItemFlag
 */
void QxtTableWidgetItem::setFlag(Qt::ItemFlag flag, bool enabled)
{
	if (enabled)
		setFlags(flags() | flag);
	else
		setFlags(flags() & ~flag);
}

void QxtTableWidgetItem::setData(int role, const QVariant& value)
{
	if (role == Qt::CheckStateRole)
	{
		const Qt::CheckState newState = static_cast<Qt::CheckState>(value.toInt());
		const Qt::CheckState oldState = static_cast<Qt::CheckState>(data(role).toInt());
		
		QTableWidgetItem::setData(role, value);
		
		if (newState != oldState)
		{
			QxtTableWidget* table = qobject_cast<QxtTableWidget*>(tableWidget());
			if (table)
			{
				emit table->itemCheckStateChanged(this);
			}
		}
	}
	else
	{
		QTableWidgetItem::setData(role, value);
	}
}
