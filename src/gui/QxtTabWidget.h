/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/



/**
\class QxtTabWidget QxtTabWidget

\ingroup gui

\brief Office like TabWidget
 

THis provides an office like tabwidget, with contextmenu on each tab.
*/

#include <QTabWidget>
#include <QxtDefines.h>



class QXT_DLLEXPORT QxtTabWidget : public QTabWidget
{
	
	Q_OBJECT
	


	public:
		/// ctor
        	QxtTabWidget(QWidget *parent = 0);
	protected:

		void contextMenuEvent ( QContextMenuEvent * event );
	signals:
		///is emited when a context menu for a specific tab 'index' is requested 
		void Context ( int index );

};
