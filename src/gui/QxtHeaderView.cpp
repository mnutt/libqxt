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





void QxtHeaderView::paintSection ( QPainter * painter, const QRect & rm, int logicalIndex ) const
	{
	QRect rect=rm;


	painter->save();
	QHeaderView::paintSection(painter,rect,logicalIndex);
	painter->restore();



	int moved =subPaint(painter, rect, logicalIndex,priv->action_size_c(),priv->space);
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

        int moved= subClick(m,priv->action_size_c(), priv->space ) ;


        int wm=width()-moved;

        if(m->x()>wm)return;

        int i=0;
        while(wm>0)
                {
                wm-=priv->action_size_c().width();
                wm-=priv->space*2;

                if (i>priv->actions.count())break;

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
    reimplement this to add your own icons or widgets to the header.\n
    it must return the width you took for your own drawing, so the other icons will start behind that.
    do not forget to reimplement subClick, to at least return the taken sizte too. 
 */

int QxtHeaderView::subPaint(QPainter * , const QRect & , int ,QSize , int ) const
        {
        return 0;
        }
/*!
    reimplement this to add your own icons or widgets to the header.\n
    it must return the width you took for your own drawing, so the other icons will start behind that.
 */

int QxtHeaderView::subClick(QMouseEvent * ,QSize , int) 
        {
        return 0;
        }

