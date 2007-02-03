/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtTreeWidget.h"
#include "QxtTreeWidget_p.h"
#include "QxtItemDelegate.h"
#include <QHeaderView>

QxtItemDelegate* QxtTreeWidgetPrivate::delegate() const
{
	return dynamic_cast<QxtItemDelegate*>(qxt_p().itemDelegate());
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
	if (item && !item->parent())
		qxt_p().setItemExpanded(item, !qxt_p().isItemExpanded(item));
}

/*!
    \class QxtTreeWidget QxtTreeWidget
    \ingroup gui
    \brief An extended tree widget.

    QxtTreeWidget blaablaa.

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
    Constructs a new QxtTreeWidget with \a parent.
 */
QxtTreeWidget::QxtTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
	QXT_INIT_PRIVATE(QxtTreeWidget);
	setItemDelegate(new QxtItemDelegate(this));
	setRootIsDecorated(false);
	setColumnCount(1);
	header()->hide();
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
    \property QxtTreeWidget::rootDecorated
    \brief This property holds whether top level items are decorated

    Top level items are decorated if this property is \b true.
    The default value is \b true.

    \sa decorationStyle elideMode 
 */
bool QxtTreeWidget::isRootDecorated() const
{
	Q_ASSERT(qxt_d().delegate());
	return qxt_d().delegate()->isRootDecorated();
}

void QxtTreeWidget::setRootDecorated(bool decorate)
{
	Q_ASSERT(qxt_d().delegate());
	return qxt_d().delegate()->setRootDecorated(decorate);
}

/*!
    \property QxtItemDelegate::decorationStyle
    \brief This property holds the top level item decoration style

    Top level items are decorated according to this property.
    The default value is \b QxtItemDelegate::Buttonlike.

    \note The property has effect only in case rootDecorated is \b true.

    \sa rootDecorated QxtItemDelegate::DecorationStyle
 */
QxtItemDelegate::DecorationStyle QxtTreeWidget::decorationStyle() const
{
	Q_ASSERT(qxt_d().delegate());
	return qxt_d().delegate()->decorationStyle();
}

void QxtTreeWidget::setDecorationStyle(QxtItemDelegate::DecorationStyle style)
{
	Q_ASSERT(qxt_d().delegate());
	return qxt_d().delegate()->setDecorationStyle(style);
}

/*!
    \property QxtTreeWidget::elideMode
    \brief This property holds the text elide mode

    The text of a decorated top level item is elided according to this property.
    The default value is \b Qt::ElideMiddle.

    \note The property has effect only in case rootDecorated is \b true.

    \sa rootDecorated
 */
Qt::TextElideMode QxtTreeWidget::elideMode() const
{
	Q_ASSERT(qxt_d().delegate());
	return qxt_d().delegate()->elideMode();
}

void QxtTreeWidget::setElideMode(Qt::TextElideMode mode)
{
	Q_ASSERT(qxt_d().delegate());
	return qxt_d().delegate()->setElideMode(mode);
}
