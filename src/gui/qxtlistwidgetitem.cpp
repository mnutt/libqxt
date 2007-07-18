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
#include "qxtlistwidgetitem.h"
#include "qxtlistwidget.h"

/*!
    \class QxtListWidgetItem QxtListWidgetItem
    \ingroup gui
    \brief An extended QListWidgetItem.

    QxtListWidgetItem provides means for offering check state change signals and
    convenience methods for testing and setting flags.

    \sa QxtListWidget
 */


QxtListWidgetItem::QxtListWidgetItem(QListWidget* parent, int type)
	: QListWidgetItem(parent, type)
{
}

QxtListWidgetItem::QxtListWidgetItem(const QString& text, QListWidget* parent, int type)
	: QListWidgetItem(text, parent, type)
{
}

QxtListWidgetItem::QxtListWidgetItem(const QIcon& icon, const QString& text, QListWidget* parent, int type)
	: QListWidgetItem(icon, text, parent, type)
{
}

QxtListWidgetItem::QxtListWidgetItem(const QxtListWidgetItem& other)
	: QListWidgetItem(other)
{
}

QxtListWidgetItem::~QxtListWidgetItem()
{
}

/*!
    Returns \b true if the \a flag is set, otherwise \b false.

    \sa setFlag(), QListWidgetItem::flags(), Qt::ItemFlag
 */
bool QxtListWidgetItem::testFlag(Qt::ItemFlag flag) const
{
	return (flags() & flag);
}

/*!
    If \a enabled is \b true, the item \a flag is enabled; otherwise, it is disabled.

    \sa testFlag(), QListWidgetItem::setFlags(), Qt::ItemFlag
 */
void QxtListWidgetItem::setFlag(Qt::ItemFlag flag, bool enabled)
{
	if (enabled)
		setFlags(flags() | flag);
	else
		setFlags(flags() & ~flag);
}

void QxtListWidgetItem::setData(int role, const QVariant& value)
{
	if (role == Qt::CheckStateRole)
	{
		const Qt::CheckState newState = static_cast<Qt::CheckState>(value.toInt());
		const Qt::CheckState oldState = static_cast<Qt::CheckState>(data(role).toInt());
		
		QListWidgetItem::setData(role, value);
		
		if (newState != oldState)
		{
			QxtListWidget* list = qobject_cast<QxtListWidget*>(listWidget());
			if (list)
			{
				emit list->itemCheckStateChanged(this);
			}
		}
	}
	else
	{
		QListWidgetItem::setData(role, value);
	}
}
