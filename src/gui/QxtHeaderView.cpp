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
		space=10;
              action_size=NULL;
              }

        QSize action_size_c() const
                {
                return *action_size;
                }

        QList<QAction *> actions;
	QSize * action_size;
	int space;

    };


/*!
    \class QxtHeaderView QxtHeaderView
    \ingroup gui
    \brief a headerview that can have QActions

    draws actions directly into the header. it's like a toolbar for your ItemView.

    \image html qxtheaderview.png "QxtHeaderView with a few actions."
 */

/*!
    \fn QxtHeaderView::QxtHeaderView()

   default Constructor
 */

QxtHeaderView::QxtHeaderView (Qt::Orientation o ,QWidget *parent):QHeaderView(o,parent)
	{
        priv = new QxtHeaderViewPrivate;
	setStretchLastSection(true);
	QStyleOptionViewItem  option;
	option.initFrom(this);
	priv->action_size= new QSize( QApplication::style()->subElementRect(QStyle::SE_ViewItemCheckIndicator,&option).size());
        setMouseTracking (true );
	}



//-----------------------------------------------------------------
/*!
    adds a new QAction \a action to the header.
 */
void QxtHeaderView::addAction(QAction * action)
	{
	priv->actions.append(action);
	}

//-----------------------------------------------------------------

void  QxtHeaderView::mouseMoveEvent ( QMouseEvent * m )
        {
	if (!priv->action_size){setToolTip (QString()); leaveEvent ( m );     return;}
	int moved = subWidth(priv->action_size_c(),priv->space);
        int wm=width()-moved;
        if(m->x()>wm){setToolTip (QString());leaveEvent ( m );  return;}
        int i=0;
        while(wm>0)
                {
                wm-=priv->action_size_c().width();
                wm-=priv->space*2;

                if (i>(priv->actions.count()-1))break;

                if (m->x() >  wm)
                        {
                        setToolTip (priv->actions[i]->toolTip ());
                        return;
                        }
                i++;
                }

        setToolTip (QString());
        leaveEvent ( m );

        }


void QxtHeaderView::paintSection ( QPainter * painter, const QRect & rm, int logicalIndex ) const
	{
	QRect rect=rm;


	painter->save();
	QHeaderView::paintSection(painter,rect,logicalIndex);
	painter->restore();


        subPaint(painter, rect, logicalIndex,priv->action_size_c(),priv->space);
	int moved = subWidth(priv->action_size_c(),priv->space);
	rect.adjust(0,0,-moved,0);

	rect.adjust(0,0,-priv->space,0);
	QAction * a;
	foreach(a, priv->actions)
		{
		QIcon img = a->icon();
		QRect r=QStyle::alignedRect ( Qt::LeftToRight, Qt::AlignRight | Qt::AlignVCenter, *priv->action_size,rect);
 		img.paint(painter, r.x(), r.y(), r.width(), r.height(), Qt::AlignCenter);
		rect.adjust(0,0,-priv->action_size->width()-priv->space,0);	///shrink the available space rect
		}
	}

void  QxtHeaderView::mousePressEvent ( QMouseEvent * m )
	{
	if (!priv->action_size)return;

        subClick(m,priv->action_size_c(), priv->space ) ;
	int moved = subWidth(priv->action_size_c(),priv->space);


        int wm=width()-moved;

        if(m->x()>wm)return;

        int i=0;
        while(wm>0)
                {
                wm-=priv->action_size_c().width();
                wm-=priv->space*2;

                if (i>(priv->actions.count()-1))break;

                if (m->x() >  wm)
                        {
                        priv->actions[i]->trigger();
                        break;
                        }

                i++;
                }


//                 v
//         | x | x | x |

	}


//-----------------------------------------------------------------
/*!
        reimplement this to add your own icons, widgets, or whatever to the header.\n
 */

void QxtHeaderView::subPaint(QPainter * , const QRect & , int ,QSize , int ) const
        {
        }
/*! 
        reimplement this to receive clicks to your own icons,widgets, etc...
 */

void QxtHeaderView::subClick(QMouseEvent * ,QSize , int) 
        {

        }
/*! 
        when reimplementing subPaint and/or subClick  you must also override this function and return the width your custom drawing takes,
        so the QActions know where to start.
 */

int QxtHeaderView::subWidth(QSize , int ) const
        {
        return 0;
        }
