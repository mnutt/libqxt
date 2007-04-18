#include "QxtHeaderView.h"
#include "QxtHeaderView_p.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QMouseEvent>
#include <QAction>


QxtHeaderView::QxtHeaderView (Qt::Orientation o ,CategorieTree *parent):QHeaderView(o,parent)
	{
	QXT_INIT_PRIVATE (QxtHeaderView);
	qxt_d()->construct();
	}


void QxtHeaderViewPrivate::construct();
	{
	action_size=NULL;
	setStretchLastSection(true);
	QStyleOptionViewItem  option;
	option.initFrom(this);
	action_size= new QSize( QApplication::style()->subElementRect(QStyle::SE_ViewItemCheckIndicator,&option).size());
	}


//-----------------------------------------------------------------

void QxtHeaderView::addAction(QAction * a)
	{
	qxt_d()->addAction(a);
	}
void QxtHeaderViewPrivate::addAction(QAction * a)
	{
	actions.append(a);
	}

//-----------------------------------------------------------------





void QxtHeaderViewPrivate::paintSection ( QPainter * painter, const QRect & rm, int logicalIndex ) const
	{
	QRect rect=rm;

	painter->save();
	QHeaderView::paintSection(painter,rect,logicalIndex);
	painter->restore();



	int moved =qxt_p()->subPaint(painter, rect, logicalIndex,*action_size,10);
	rect.adjust(0,0,-moved,0);


	QAction * a;
	foreach(a, actions)
		{
		rect.adjust(0,0,-action_size->width()-10,0);	///shrink the available space rect
		QIcon img = a->icon();
		QRect r=QStyle::alignedRect ( Qt::LeftToRight, Qt::AlignRight | Qt::AlignVCenter, *action_size,rect);
 		img.paint(painter, r.x(), r.y(), r.width(), r.height(), Qt::AlignCenter);
		}
	}

void  QxtHeaderViewPrivate::mousePressEvent ( QMouseEvent * m )
	{
	if (!action_size)return;

	
	if ( m->x()>(width()-action_size->width()-10))
		{
		if (actions.count()>0)
			actions[0]->trigger();
		}
	else if ( m->x()>(width()-(action_size->width()*2)-20))
		{
		if (actions.count()>1)
			actions[1]->trigger();
		}
	else if ( m->x()>(width()-(action_size->width()*3)-30))
		{
		if (actions.count()>2)
			actions[2]->trigger();
		}

	}


//-----------------------------------------------------------------


int QxtHeaderView::subPaint(QPainter * painter, const QRect & rect, int logicalIndex,QSize icon_size, int spacing);
	{
	return 0;
	}


