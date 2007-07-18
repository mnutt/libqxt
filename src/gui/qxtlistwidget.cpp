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
#include "qxtlistwidget.h"
#include "qxtitemdelegate.h"
#include "qxtlistwidget_p.h"

QxtListWidgetPrivate::QxtListWidgetPrivate()
{
}

void QxtListWidgetPrivate::informStartEditing(const QModelIndex& index)
{
	QListWidgetItem* item = qxt_p().itemFromIndex(index);
	Q_ASSERT(item);
	emit qxt_p().itemEditingStarted(item);
}

void QxtListWidgetPrivate::informFinishEditing(const QModelIndex& index)
{
	QListWidgetItem* item = qxt_p().itemFromIndex(index);
	Q_ASSERT(item);
	emit qxt_p().itemEditingFinished(item);
}

/*!
    \class QxtListWidget QxtListWidget
    \ingroup gui
    \brief An extended QListWidget with additional signals.

    QxtListWidget offers a few most commonly requested signals.

    \image html qxtlistwidget.png "QxtListWidget in Plastique style."
 */

/*!
    \fn QxtListWidget::itemEditingStarted(QListWidgetItem* item)

    This signal is emitted after the editing of \a item has been started.

    \sa itemEditingFinished()
 */

/*!
    \fn QxtListWidget::itemEditingFinished(QListWidgetItem* item)

    This signal is emitted after the editing of \a item has been finished.

    \sa itemEditingStarted()
 */

/*!
    \fn QxtListWidget::itemCheckStateChanged(QxtListWidgetItem* item)

    This signal is emitted whenever the check state of \a item has changed.

    \note Use QxtListWidgetItem in order to enable this feature.

    \sa QxtListWidgetItem, QListWidgetItem::checkState()
 */

/*!
    Constructs a new QxtListWidget with \a parent.
 */
QxtListWidget::QxtListWidget(QWidget* parent) : QListWidget(parent)
{
	QXT_INIT_PRIVATE(QxtListWidget);
	QxtItemDelegate* delegate = new QxtItemDelegate(this);
	connect(delegate, SIGNAL(editingStarted(const QModelIndex&)),
		&qxt_d(), SLOT(informStartEditing(const QModelIndex&)));
	connect(delegate, SIGNAL(editingFinished(const QModelIndex&)),
		&qxt_d(), SLOT(informFinishEditing(const QModelIndex&)));
	setItemDelegate(delegate);
}

/*!
    Destructs the list widget.
 */
QxtListWidget::~QxtListWidget()
{
}
