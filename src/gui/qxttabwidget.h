/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/


#ifndef QXTTABWIDGET_H
#define QXTTABWIDGET_H

#include <QTabWidget>
#include "qxtnamespace.h"
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtTabWidgetPrivate;

class QXT_GUI_EXPORT QxtTabWidget : public QTabWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtTabWidget);
	Q_PROPERTY(Qt::ContextMenuPolicy tabContextMenuPolicy READ tabContextMenuPolicy WRITE setTabContextMenuPolicy)
	
public:
	explicit QxtTabWidget(QWidget* parent = 0);
	virtual ~QxtTabWidget();
	
	Qt::ContextMenuPolicy tabContextMenuPolicy() const;
	void setTabContextMenuPolicy(Qt::ContextMenuPolicy policy);
	
	void addTabAction(int index, QAction* action);
	void addTabActions(int index, QList<QAction*> actions);
	void clearTabActions(int index);
	void insertTabAction(int index, QAction* before, QAction* action);
	void insertTabActions(int index, QAction* before, QList<QAction*> actions);
	void removeTabAction(int index, QAction* action);
	QList<QAction*> tabActions(int index) const;
	
signals:
	void tabContextMenuRequested(int index, const QPoint& globalPos);
	
protected:
#ifndef QXT_DOXYGEN_RUN
	virtual void tabInserted(int index);
	virtual void tabRemoved(int index);
	
	virtual void contextMenuEvent(QContextMenuEvent* event);
#endif // QXT_DOXYGEN_RUN
	virtual void tabContextMenuEvent(int index, QContextMenuEvent* event);
};

#endif // QXTQXTTABWIDGET_H
