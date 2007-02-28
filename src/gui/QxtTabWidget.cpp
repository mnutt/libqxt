/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtTabWidget.h"
#include <QContextMenuEvent>
#include <QApplication>
#include <QTabBar>
#include <QAction>
#include <QMenu>

typedef QList<QAction*> Actions;

class QxtTabWidgetPrivate : public QxtPrivate<QxtTabWidget>
{
public:
	QXT_DECLARE_PUBLIC(QxtTabWidget);
	
	int tabIndexAt(const QPoint& pos) const;
	
	QList<Actions> actions;
	Qt::ContextMenuPolicy policy;
};

int QxtTabWidgetPrivate::tabIndexAt(const QPoint& pos) const
{
	const int count = qxt_p().count();
	const QTabBar* tabBar = qxt_p().tabBar();
	for (int i = 0; i < count; ++i)
		if (tabBar->tabRect(i).contains(pos))
			return i;
	return -1;
}

/*!
    \class QxtTabWidget QxtTabWidget
    \ingroup gui
    \brief An extended QTabWidget.

    QxtTabWidget provides some convenience for handling tab specific context menus.

    Tab specific close buttons and movable tabs are already on the way, so I won't
    bother with them for now as it would require a whole lot of rewriting anyway.

    http://www.trolltech.com/developer/task-tracker/index_html?method=entry&id=137891
 */

/*!
    \fn QxtTabWidget::tabContextMenuRequested(int index, const QPoint& globalPos)

    This signal is emitted whenever the context menu is requested over
    tab at \a index at \a globalPos.
 */

/*!
    Constructs a new QxtTabWidget with \a parent.
 */
QxtTabWidget::QxtTabWidget(QWidget* parent) : QTabWidget(parent)
{
	QXT_INIT_PRIVATE(QxtTabWidget);
}

/*!
    Destructs the tab widget.
 */
QxtTabWidget::~QxtTabWidget()
{
}

/*!
    \property QxtTabWidget::tabContextMenuPolicy
    \brief This property holds how the tab specific context menus are handled.

    The default value of this property is \b Qt::DefaultContextMenu,
    which means the tabContextMenuEvent() handler is called. Other values
    are \b Qt::NoContextMenu, \b Qt::PreventContextMenu,
    \b Qt::ActionsContextMenu, and \b Qt::CustomContextMenu. With
    \b Qt::CustomContextMenu, the signal tabContextMenuRequested() is
    emitted.

    \sa tabContextMenuEvent(), tabContextMenuRequested(), tabActions()
 */
Qt::ContextMenuPolicy QxtTabWidget::tabContextMenuPolicy() const
{
	return qxt_d().policy;
}

void QxtTabWidget::setTabContextMenuPolicy(Qt::ContextMenuPolicy policy)
{
	qxt_d().policy = policy;
}

/*!
    Appends the \a action to the list of actions of the
    tab at \a index.

    \sa removeTabAction(), insertTabAction(), tabActions()
 */
void QxtTabWidget::addTabAction(int index, QAction* action)
{
	insertTabAction(index, 0, action);
}

/*!
    Appends the \a actions to the list of actions of the
    tab at \a index.

    \sa removeTabAction(), addTabAction()
 */
void QxtTabWidget::addTabActions(int index, QList<QAction*> actions)
{
	foreach (QAction* action, actions)
	{
		insertTabAction(index, 0, action);
	}
}

/*!
    Clears the list of actions of the tab at \a index.

    \sa removeTabAction(), addTabAction()
 */
void QxtTabWidget::clearTabActions(int index)
{
	Q_ASSERT(index >= 0 && index < qxt_d().actions.count());
	
	while (qxt_d().actions[index].count())
	{
		QAction* action = qxt_d().actions[index].takeLast();
		QActionEvent e(QEvent::ActionRemoved, action);
		QApplication::sendEvent(this, &e);
		delete action;
	}
}

/*!
    Inserts the \a action to the list of actions of the
    tab at \a index, before the action \a before. It appends
    the action if \a before is \c 0.

    \sa removeTabAction(), addTabAction(), tabContextMenuPolicy, tabActions()
 */
void QxtTabWidget::insertTabAction(int index, QAction* before, QAction* action)
{
	Q_ASSERT(index >= 0 && index < qxt_d().actions.count());
	
	if (!action)
	{
		qWarning("QxtTabWidget::insertTabAction: Attempt to insert a null action");
		return;
	}
	
	const Actions& actions = qxt_d().actions.at(index);
	if (actions.contains(action))
		removeTabAction(index, action);

	int pos = actions.indexOf(before);
	if (pos < 0)
	{
		before = 0;
		pos = actions.count();
	}
	qxt_d().actions[index].insert(pos, action);

// TODO: ouch, i really didn't think of anything like this would come up! :)
//	QActionPrivate *apriv = action->d_func();
//	apriv->widgets.append(this);

	QActionEvent e(QEvent::ActionAdded, action, before);
	QApplication::sendEvent(this, &e);
}

/*!
    Inserts the \a actions to the list of actions of the
    tab at \a index, before the action \a before. It appends
    the action if \a before is \c 0.

    \sa removeAction(), QMenu, insertAction(), contextMenuPolicy
 */
void QxtTabWidget::insertTabActions(int index, QAction* before, QList<QAction*> actions)
{
	foreach (QAction* action, actions)
	{
		insertTabAction(index, before, action);
	}
}

/*!
    Removes the action \a action from the list of actions of the
    tab at \a index.

    \sa insertTabAction(), tabActions(), insertTabAction()
 */
void QxtTabWidget::removeTabAction(int index, QAction* action)
{
	Q_ASSERT(index >= 0 && index < qxt_d().actions.count());
	
	if (!action)
	{
		qWarning("QxtTabWidget::removeTabAction: Attempt to remove a null action");
		return;
	}

// TODO: ouch, i really didn't think of anything like this would come up! :)
//	QActionPrivate *apriv = action->d_func();
//	apriv->widgets.removeAll(this);

	if (qxt_d().actions[index].removeAll(action))
	{
		QActionEvent e(QEvent::ActionRemoved, action);
		QApplication::sendEvent(this, &e);
	}
}

/*!
    Returns the (possibly empty) list of actions for the
    tab at \a index.

    \sa tabContextMenuPolicy, insertTabAction(), removeTabAction()
 */
QList<QAction*> QxtTabWidget::tabActions(int index) const
{
	Q_ASSERT(index >= 0 && index < qxt_d().actions.count());
	return qxt_d().actions.at(index);
}

void QxtTabWidget::tabInserted(int index)
{
	Q_ASSERT(index >= 0 && index <= qxt_d().actions.count());
	qxt_d().actions.insert(index, Actions());
}

void QxtTabWidget::tabRemoved(int index)
{
	Q_ASSERT(index >= 0 && index < qxt_d().actions.count());
	qxt_d().actions.removeAt(index);
}

void QxtTabWidget::contextMenuEvent(QContextMenuEvent* event)
{
	const QPoint& pos = event->pos();
	if (!tabBar()->geometry().contains(pos))
		return QTabWidget::contextMenuEvent(event);
	
	const int index = qxt_d().tabIndexAt(event->pos());
	switch (qxt_d().policy)
	{
		case Qt::NoContextMenu:
			event->ignore();
			break;
			
		case Qt::PreventContextMenu:
			event->accept();
			break;
		
		case Qt::ActionsContextMenu:
			if (index != -1 && qxt_d().actions.at(index).count())
			{
				QMenu::exec(qxt_d().actions.at(index), event->globalPos());
			}
			break;
			
		case Qt::CustomContextMenu:
			if (index != -1)
			{
				emit tabContextMenuRequested(index, event->globalPos());
			}
			break;
			
		case Qt::DefaultContextMenu:
		default:
			if (index != -1)
			{
				tabContextMenuEvent(index, event);
			}
	}
}

/*!
    This event handler, for event \a event, can be reimplemented in a
    subclass to receive context menu events for the tab at \a index.

    The handler is called when \l tabContextMenuPolicy is
    \b Qt::DefaultContextMenu.

    The default implementation ignores the context menu event.

    \sa tabContextMenuRequested()
 */
void QxtTabWidget::tabContextMenuEvent(int index, QContextMenuEvent* event)
{
	Q_UNUSED(index);
	event->ignore();
}
