#include "QxtHeaderView.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QMouseEvent>
#include <QAction>


class QxtHeaderViewPrivate
    {
    public:

        QxtHeaderViewPrivate()
              {
              action_size=NULL;
              }

        QSize action_size_c() const
                {
                return *action_size;
                }

        QList<QAction *> actions;
	QSize * action_size;

    };




QxtHeaderView::QxtHeaderView (Qt::Orientation o ,QWidget *parent):QHeaderView(o,parent)
	{
        priv = new QxtHeaderViewPrivate;
	setStretchLastSection(true);
	QStyleOptionViewItem  option;
	option.initFrom(this);
	priv->action_size= new QSize( QApplication::style()->subElementRect(QStyle::SE_ViewItemCheckIndicator,&option).size());
	}



//-----------------------------------------------------------------

void QxtHeaderView::addAction(QAction * a)
	{
	priv->actions.append(a);
	}

//-----------------------------------------------------------------





void QxtHeaderView::paintSection ( QPainter * painter, const QRect & rm, int logicalIndex ) const
	{
	QRect rect=rm;

	painter->save();
	QHeaderView::paintSection(painter,rect,logicalIndex);
	painter->restore();



	int moved =subPaint(painter, rect, logicalIndex,priv->action_size_c(),10);
	rect.adjust(0,0,-moved,0);


	QAction * a;
	foreach(a, priv->actions)
		{
		rect.adjust(0,0,-priv->action_size->width()-10,0);	///shrink the available space rect
		QIcon img = a->icon();
		QRect r=QStyle::alignedRect ( Qt::LeftToRight, Qt::AlignRight | Qt::AlignVCenter, *priv->action_size,rect);
 		img.paint(painter, r.x(), r.y(), r.width(), r.height(), Qt::AlignCenter);
		}
	}

void  QxtHeaderView::mousePressEvent ( QMouseEvent * m )
	{
	if (!priv->action_size)return;

	
	if ( m->x()>(width()-priv->action_size->width()-10))
		{
		if (priv->actions.count()>0)
			priv->actions[0]->trigger();
		}
	else if ( m->x()>(width()-(priv->action_size->width()*2)-20))
		{
		if (priv->actions.count()>1)
			priv->actions[1]->trigger();
		}
	else if ( m->x()>(width()-(priv->action_size->width()*3)-30))
		{
		if (priv->actions.count()>2)
			priv->actions[2]->trigger();
		}

	}


//-----------------------------------------------------------------


int QxtHeaderView::subPaint(QPainter * , const QRect & , int ,QSize , int ) const
	{
	return 0;
	}


