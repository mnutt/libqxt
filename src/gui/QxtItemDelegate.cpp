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


#include "QxtItemDelegate.h"
#include <QTreeView>
#include <QPainter>

static const int TOP_LEVEL_EXTENT = 2;

class QxtItemDelegatePrivate : public QxtPrivate<QxtItemDelegate>
{
public:
	QXT_DECLARE_PUBLIC(QxtItemDelegate);
	QxtItemDelegatePrivate();
	
	void paintButton(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const;
	void paintMenu(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const;
	
	Qxt::DecorationStyle style;
	Qt::TextElideMode elide;
};

QxtItemDelegatePrivate::QxtItemDelegatePrivate() :
	style(Qxt::NoDecoration),
	elide(Qt::ElideMiddle)
{
}

void QxtItemDelegatePrivate::paintButton(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const
{
	// draw the button
	QStyleOptionButton buttonOption;
	buttonOption.state = option.state;
#ifdef Q_WS_MAC
	buttonOption.state |= QStyle::State_Raised;
#endif
	buttonOption.state &= ~QStyle::State_HasFocus;
	if (view->isExpanded(index))
		buttonOption.state |= QStyle::State_Sunken;

	buttonOption.rect = option.rect;
	buttonOption.palette = option.palette;
	buttonOption.features = QStyleOptionButton::None;
	view->style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter, view);

	// draw the branch indicator
	static const int i = 9;
	const QRect& r = option.rect;
	if (index.model()->hasChildren(index))
	{
		QStyleOption branchOption;
		branchOption.rect = QRect(r.left() + i/2, r.top() + (r.height() - i)/2, i, i);
		branchOption.palette = option.palette;
		branchOption.state = QStyle::State_Children;
		if (view->isExpanded(index))
			branchOption.state |= QStyle::State_Open;
		view->style()->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, painter, view);
	}

	// draw the text
	QRect textrect = QRect(r.left() + i*2, r.top(), r.width() - ((5*i)/2), r.height());
	QString text = option.fontMetrics.elidedText(index.data().toString(), elide, textrect.width());
	view->style()->drawItemText(painter, textrect, Qt::AlignCenter, option.palette, view->isEnabled(), text);
}

void QxtItemDelegatePrivate::paintMenu(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const
{
	// draw the menu bar item
	QStyleOptionMenuItem menuOption;
	menuOption.palette = view->palette();
	menuOption.fontMetrics = view->fontMetrics();
	menuOption.state = QStyle::State_None;
	if (view->isEnabled() && index.flags() & Qt::ItemIsEnabled)
		menuOption.state |= QStyle::State_Enabled;
	else
		menuOption.palette.setCurrentColorGroup(QPalette::Disabled);
	menuOption.state |= QStyle::State_Selected;
	menuOption.state |= QStyle::State_Sunken;
	menuOption.state |= QStyle::State_HasFocus;
	menuOption.rect = option.rect;
	menuOption.text = index.data().toString();
	menuOption.icon = QIcon(index.data(Qt::DecorationRole).value<QPixmap>());
	view->style()->drawControl(QStyle::CE_MenuBarItem, &menuOption, painter, view);
	
	// draw the an arrow as a branch indicator
	if (index.model()->hasChildren(index))
	{
		QStyle::PrimitiveElement arrow;
		if (view->isExpanded(index))
			arrow = QStyle::PE_IndicatorArrowUp;
		else
			arrow = QStyle::PE_IndicatorArrowDown;
		static const int i = 9;
		const QRect& r = option.rect;
		menuOption.rect = QRect(r.left() + i/2, r.top() + (r.height() - i)/2, i, i);
		view->style()->drawPrimitive(arrow, &menuOption, painter, view);
	}
}

/*!
    \class QxtItemDelegate QxtItemDelegate
    \ingroup gui
    \brief An extended item delegate.

    QxtItemDelegate provides signals for starting and finishing of editing
    and an optional decoration for top level indices in a single column QTreeView.

    \note Set \b QTreeView::rootIsDecorated to \b false to avoid multiple branch indicators.

    \note Requires Qt 4.2 or newer.
 */

/*!
    \fn QxtItemDelegate::editingStarted(const QModelIndex& index)

    This signal is emitted immediately after the editing of \a index has been started.

    \sa editingFinished()
 */

/*!
    \fn QxtItemDelegate::editingFinished(const QModelIndex& index)

    This signal is emitted immediately after the editing of \a index has been finished.

    \sa editingStarted()
 */

/*!
    Constructs a new QxtItemDelegate with \a parent.
 */
QxtItemDelegate::QxtItemDelegate(QObject* parent) : QItemDelegate(parent)
{
	QXT_INIT_PRIVATE(QxtItemDelegate);
}

/*!
    Destructs the item delegate.
 */
QxtItemDelegate::~QxtItemDelegate()
{
}

/*!
    \property QxtItemDelegate::decorationStyle
    \brief This property holds the top level index decoration style

    Top level indices are decorated according to this property.
    The default value is \b Qxt::NoDecoration.

    \note The property has effect only in case the delegate
    is installed on a single column QTreeView. The view must
    be the parent of the delegate.

    \sa Qxt::DecorationStyle
 */
Qxt::DecorationStyle QxtItemDelegate::decorationStyle() const
{
	return qxt_d().style;
}

void QxtItemDelegate::setDecorationStyle(Qxt::DecorationStyle style)
{
	qxt_d().style = style;
}

/*!
    \property QxtItemDelegate::elideMode
    \brief This property holds the text elide mode

    The text of a decorated top level index is elided according to this property.
    The default value is \b Qt::ElideMiddle.

    \note The property has effect only for decorated top level indices.

    \sa decorationStyle
 */
Qt::TextElideMode QxtItemDelegate::elideMode() const
{
	return qxt_d().elide;
}

/*!
    \internal
 */
void QxtItemDelegate::setElideMode(Qt::TextElideMode mode)
{
	qxt_d().elide = mode;
}

/*!
    \internal
 */
void QxtItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	QItemDelegate::setEditorData(editor, index);
	emit const_cast<QxtItemDelegate*>(this)->editingStarted(index);
}

/*!
    \internal
 */
void QxtItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	QItemDelegate::setModelData(editor, model, index);
	emit const_cast<QxtItemDelegate*>(this)->editingFinished(index);
}

/*!
    \internal
 */
void QxtItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	const QAbstractItemModel* model = index.model();
	const QTreeView* view = dynamic_cast<QTreeView*>(parent());
	const bool topLevel = !index.parent().isValid();
	const bool singleColumn = (model->columnCount() == 1);
	
	if (view && topLevel && singleColumn)
	{
		switch (qxt_d().style)
		{
			case Qxt::Buttonlike:
				qxt_d().paintButton(painter, option, index, view);
				break;
			case Qxt::Menulike:
				qxt_d().paintMenu(painter, option, index, view);
				break;
			default:
				QItemDelegate::paint(painter, option, index);
				break;
		}
	}
	else
	{
		QItemDelegate::paint(painter, option, index);
	}
}

/*!
    \internal
 */
QSize QxtItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	// something slightly bigger for top level indices
	QSize size = QItemDelegate::sizeHint(option, index);
	if (!index.parent().isValid())
		size += QSize(TOP_LEVEL_EXTENT, TOP_LEVEL_EXTENT);
	return  size;
}
