/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Adam Higerd and Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtTreeWidget.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QHeaderView>
#include <QMouseEvent>
#include <QMimeData>
#include <QApplication>
#include <QByteArray>
#include <QDebug>



QxtTreeWidget::QxtTreeWidget(QWidget * parent) :QTreeWidget(parent)
{
	dragstartitem=0;
}






void QxtTreeWidget::drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index )const
{
    if (index.parent() == QModelIndex()) {
        QStyleOptionButton button;

        button.rect = option.rect;
        button.rect.setWidth(header()->width());
        if(isExpanded(index)) button.state = QStyle::State_Sunken; else button.state = QStyle::State_Raised;
        style()->drawControl(QStyle::CE_PushButton, &button, painter, this);

        button.rect.setX(indentation());
        button.rect.setWidth(width() - indentation());
        painter->drawText(button.rect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine,
                model()->data(index, Qt::DisplayRole).toString());

        button.rect.setX(option.rect.left());
        button.rect.setWidth(indentation());
        drawBranches(painter, button.rect, index);
    } else {
        QTreeWidget::drawRow(painter, option, index);
    }
}





void QxtTreeWidget::mousePressEvent(QMouseEvent *event)
{

	QTreeWidgetItem *i = itemAt(event->pos());

	if (i)
		{
		if ( i->parent())
			{
			dragstartitem = i;
			QTreeWidget::mousePressEvent(event);

			}
		else
			{
			dragstartitem =0;
			
    			if(isItemExpanded(i))
        			collapseItem(i);
    			else
        			expandItem(i);

			}
		}
	else
		{
		dragstartitem =0;
		QTreeWidget::mousePressEvent(event);
		}

	if (event->button() == Qt::LeftButton)
        	dragStartPosition = event->pos();

	
}



void QxtTreeWidget::mouseMoveEvent(QMouseEvent *event)
{

if (event->button() == Qt::LeftButton)
{

    if (!dragstartitem)
        return;
    if ((event->pos() - dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

	startDrag(model()->supportedDragActions());
	dragstartitem =0;

}


QTreeWidgetItem *i = itemAt(event->pos());

  if ((i) && ( i->parent())) 
  	QTreeWidget::mouseMoveEvent(event);


}

void QxtTreeWidget::mouseReleaseEvent(QMouseEvent *event)

{
/*QTreeWidgetItem *i = itemAt(event->pos());
 if ((i) && (! i->parent())) return;*/
QTreeWidget::mouseReleaseEvent(event);
}


QTreeWidgetItem * QxtTreeWidget::ItemDragStarted()
{
return dragstartitem;
}


