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


#ifndef QXTTREEWIDGET_H
#define QXTTREEWIDGET_H

#include <QTreeWidget>
#include <qxtglobal.h>
#include <qxtnamespace.h>
#include <QxtPimpl.h>
#include "QxtTreeWidgetItem.h"

class QxtTreeWidgetPrivate;

class QXT_GUI_EXPORT QxtTreeWidget : public QTreeWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtTreeWidget);
	Q_PROPERTY(bool branchesDrawn READ branchesDrawn WRITE setBranchesDrawn)
	Q_PROPERTY(Qxt::DecorationStyle decorationStyle READ decorationStyle WRITE setDecorationStyle)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	friend class QxtTreeWidgetItem;
	
public:
	explicit QxtTreeWidget(QWidget* parent = 0);
	virtual ~QxtTreeWidget();
	
	bool branchesDrawn() const;
	void setBranchesDrawn(bool draw);
	
	Qxt::DecorationStyle decorationStyle() const;
	void setDecorationStyle(Qxt::DecorationStyle style);
	
	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);
	
signals:
	void itemEditingStarted(QTreeWidgetItem* item);
	void itemEditingFinished(QTreeWidgetItem* item);
	void itemCheckStateChanged(QxtTreeWidgetItem* item);
	
#ifndef QXT_DOXYGEN_RUN
protected:
	void drawBranches(QPainter* painter, const QRect& rect, const QModelIndex& index) const;
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTTREEWIDGET_H
