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


#include "QxtTreeWidget.h"
#include "QxtItemDelegate.h"
#include "QxtTreeWidget_p.h"
#include <QHeaderView>

QxtTreeWidgetPrivate::QxtTreeWidgetPrivate() : branches(true)
{
}

QxtItemDelegate* QxtTreeWidgetPrivate::delegate() const
{
	QxtItemDelegate* del = dynamic_cast<QxtItemDelegate*>(qxt_p().itemDelegate());
	Q_ASSERT(del);
	return del;
}

void QxtTreeWidgetPrivate::informStartEditing(const QModelIndex& index)
{
	QTreeWidgetItem* item = qxt_p().itemFromIndex(index);
	Q_ASSERT(item);
	emit qxt_p().itemEditingStarted(item);
}

void QxtTreeWidgetPrivate::informFinishEditing(const QModelIndex& index)
{
	QTreeWidgetItem* item = qxt_p().itemFromIndex(index);
	Q_ASSERT(item);
	emit qxt_p().itemEditingFinished(item);
}

void QxtTreeWidgetPrivate::expandCollapse(QTreeWidgetItem* item)
{
	if (item && !item->parent() && delegate()->decorationStyle() != Qxt::NoDecoration)
		qxt_p().setItemExpanded(item, !qxt_p().isItemExpanded(item));
}

/*!
    \class QxtTreeWidget QxtTreeWidget
    \ingroup gui
    \brief An extended tree widget.

    QxtTreeWidget offers an optional top level item decoration
    and most commonly requested signals.

    \image html qxttreewidget.png "QxtTreeWidget with Qxt::Menulike and Qxt::Buttonlike decoration styles, respectively."

    \note Requires Qt 4.2 or newer.
 */

/*!
    \fn QxtTreeWidget::itemEditingStarted(QTreeWidgetItem* item)

    This signal is emitted immediately after the editing of \a item has been started.

    \sa itemEditingFinished()
 */

/*!
    \fn QxtTreeWidget::itemEditingFinished(QTreeWidgetItem* item)

    This signal is emitted immediately after the editing of \a item has been finished.

    \sa itemEditingStarted()
 */

/*!
    \fn QxtTreeWidget::itemCheckStateChanged(QxtTreeWidgetItem* item)

    This signal is emitted whenever the check state of \a item has changed.

    \note Use QxtTreeWidgetItems in order to enable this feature.

    \sa QxtTreeWidgetItem
 */

/*!
    Constructs a new QxtTreeWidget with \a parent.
 */
QxtTreeWidget::QxtTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
	QXT_INIT_PRIVATE(QxtTreeWidget);
	setItemDelegate(new QxtItemDelegate(this));
	connect(this, SIGNAL(itemPressed(QTreeWidgetItem*, int)),
		&qxt_d(), SLOT(expandCollapse(QTreeWidgetItem*)));
}

/*!
    Destructs the tree widget.
 */
QxtTreeWidget::~QxtTreeWidget()
{
}

/*!
    \property QxtTreeWidget::branchesDrawn
    \brief This property holds whether the branches of the tree are drawn

    The default value is \b true.
 */
bool QxtTreeWidget::branchesDrawn() const
{
	return qxt_d().branches;
}

void QxtTreeWidget::setBranchesDrawn(bool draw)
{
	qxt_d().branches = draw;
}

/*!
    \property QxtTreeWidget::decorationStyle
    \brief This property holds the top level item decoration style

    Top level items are decorated according to this property.
    The default value is \b Qxt::NoDecoration.

    \note Setting the property to anything else than \b Qxt::NoDecoration
    disables root decoration, sets the column count to \b 1 and
    hides the header.

    \sa Qxt::DecorationStyle QxtItemDelegate
 */
Qxt::DecorationStyle QxtTreeWidget::decorationStyle() const
{
	return qxt_d().delegate()->decorationStyle();
}

void QxtTreeWidget::setDecorationStyle(Qxt::DecorationStyle style)
{
	if (qxt_d().delegate()->decorationStyle() != style)
	{
		qxt_d().delegate()->setDecorationStyle(style);
		
		if (style != Qxt::NoDecoration)
		{
			setRootIsDecorated(false);
			setColumnCount(1);
			header()->hide();
		}
		reset();
	}
}

/*!
    \property QxtTreeWidget::elideMode
    \brief This property holds the text elide mode

    The text of a decorated top level item is elided according to this property.
    The default value is \b Qt::ElideMiddle.

    \note The property has effect only for decorated top level items.

    \sa decorationStyle
 */
Qt::TextElideMode QxtTreeWidget::elideMode() const
{
	return qxt_d().delegate()->elideMode();
}

void QxtTreeWidget::setElideMode(Qt::TextElideMode mode)
{
	if (qxt_d().delegate()->elideMode() != mode)
	{
		qxt_d().delegate()->setElideMode(mode);
		reset();
	}
}

/*!
    \internal
 */
void QxtTreeWidget::drawBranches(QPainter* painter, const QRect& rect, const QModelIndex& index) const
{
	if (qxt_d().branches)
	{
		QTreeWidget::drawBranches(painter, rect, index);
	}
}
