/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Adam Higerd and Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

/**
\class QxtTreeWidget QxtTreeWidget

\ingroup gui

\brief QTreeWidget with a customized drawing for parent items



pretty top items, to make them more visible

hint: set the top level items SizeHint to something more big to make it look good


to implement your own drag, subclas void startDrag(Qt::DropActions );  and use QTreeWidgetItem * ItemDragStarted();  to get the item the drag started from
*/

#ifndef QXTTREEWIDGET_H
#define QXTTREEWIDGET_H


#include <QTreeWidget>
#include <QPoint>
#include <QTreeWidgetItem>
#include "QxtDefines.h"

class QXT_DLLEXPORT QxtTreeWidget : public QTreeWidget
	{
	
	Q_OBJECT
	
	public:
		QxtTreeWidget(QWidget *parent= 0);
		
		///returns a pointet to the QTreeWidgetItem the last drag started from. be warned: check if it is valid
		QTreeWidgetItem * ItemDragStarted();
		void resetDrag(){dragstartitem=0;}

	protected:

		void drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
 		void mousePressEvent(QMouseEvent *event);
 		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);


	private:
		
		QPoint  dragStartPosition;
		QTreeWidgetItem * dragstartitem;
	};


#endif
