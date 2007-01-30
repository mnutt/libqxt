/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtItemDelegate.h"
#include <QTreeView>

class QxtItemDelegatePrivate : public QxtPrivate<QxtItemDelegate>
{
public:
	QXT_DECLARE_PUBLIC(QxtItemDelegate);
	QxtItemDelegatePrivate();
	
	void paintButton(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const;
	
	bool decorate;
	QxtItemDelegate::DecorationStyle style;
	Qt::TextElideMode elide;
};

QxtItemDelegatePrivate::QxtItemDelegatePrivate() :
	decorate(true),
	style(QxtItemDelegate::Buttonlike),
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

	buttonOption.rect = option.rect;
	buttonOption.palette = option.palette;
	buttonOption.features = QStyleOptionButton::None;
	view->style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter, view);

	// draw the branch indicator
	QStyleOption branchOption;
	static const int i = 9;
	const QRect& r = option.rect;
	branchOption.rect = QRect(r.left() + i/2, r.top() + (r.height() - i)/2, i, i);
	branchOption.palette = option.palette;
	branchOption.state = QStyle::State_Children;
	if (view->isExpanded(index))
		branchOption.state |= QStyle::State_Open;
	view->style()->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, painter, view);

        // draw the text
	QRect textrect = QRect(r.left() + i*2, r.top(), r.width() - ((5*i)/2), r.height());
	QString text = option.fontMetrics.elidedText(index.data().toString(), elide, textrect.width());
	view->style()->drawItemText(painter, textrect, Qt::AlignCenter, option.palette, view->isEnabled(), text);
}

/*!
    \class QxtItemDelegate QxtItemDelegate
    \ingroup gui
    \brief An extended item delegate.

    QxtItemDelegate provides signals for starting and finishing of editing
    and an optional decoration for top level indices in a single column QTreeView.

    \note Set QTreeView::rootIsDecorated to \c false to avoid multiple branch indicators.

    \note Requires Qt 4.2 or newer.
 */

/*!
    \enum QxtItemDelegate::DecorationStyle

    This enum describes the decoration style of top level indices.

    \value Buttonlike        A buttonlike style, just like in Qt Designer's Widget Box.
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
    \property QxtItemDelegate::rootDecorated
    \brief This property holds whether top level indices are decorated

    Top level indices are decorated if this property is \c true.
    The default value is \c true.

    \note The property has effect only in case the delegate
    is installed on a single column QTreeView. The view must
    be the parent of the delegate.

    \sa decorationStyle elideMode 
 */
bool QxtItemDelegate::isRootDecorated() const
{
	return qxt_d().decorate;
}

void QxtItemDelegate::setRootDecorated(bool decorate)
{
	qxt_d().decorate = decorate;
}

/*!
    \property QxtItemDelegate::decorationStyle
    \brief This property holds the top level index decoration style

    Top level indices are decorated according to this property.
    The default value is QxtItemDelegate::Buttonlike.

    \note The property has effect only in case rootDecorated is \c true.

    \sa rootDecorated QxtItemDelegate::DecorationStyle
 */
QxtItemDelegate::DecorationStyle QxtItemDelegate::decorationStyle() const
{
	return qxt_d().style;
}

void QxtItemDelegate::setDecorationStyle(QxtItemDelegate::DecorationStyle style)
{
	qxt_d().style = style;
}

/*!
    \property QxtItemDelegate::elideMode
    \brief This property holds the text elide mode

    The text of a decorated top level item is elided according to this property.
    The default value is Qt::ElideMiddle.

    \note The property has effect only in case rootDecorated is \c true.

    \sa rootDecorated
 */
Qt::TextElideMode QxtItemDelegate::elideMode() const
{
	return qxt_d().elide;
}

void QxtItemDelegate::setElideMode(Qt::TextElideMode mode)
{
	qxt_d().elide = mode;
}

void QxtItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	QItemDelegate::setEditorData(editor, index);
	emit const_cast<QxtItemDelegate*>(this)->editingStarted(index);
}

void QxtItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	QItemDelegate::setModelData(editor, model, index);
	emit const_cast<QxtItemDelegate*>(this)->editingFinished(index);
}

void QxtItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	const QAbstractItemModel* model = index.model();
	const QTreeView* view = dynamic_cast<QTreeView*>(parent());
	const bool topLevel = !index.parent().isValid();
	const bool singleColumn = (model->columnCount() == 1);
	
	if (qxt_d().decorate && view && topLevel && singleColumn)
	{
		switch (qxt_d().style)
		{
			case Buttonlike:
				qxt_d().paintButton(painter, option, index, view);
				break;
			default:
				// nothing to do
				break;
		}
	}
	else
	{
		QItemDelegate::paint(painter, option, index);
	}
}

QSize QxtItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return QItemDelegate::sizeHint(option, index) + QSize(2, 2);
}
