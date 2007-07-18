/****************************************************************************
**
** Copyright (C) J-P Nurmi <jpnurmi@gmail.com>. Some rights reserved.
**
** This file is part of the QxtGui module of the
** Qt eXTension library <http://libqxt.sourceforge.net>
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef QXTTABLEWIDGET_H
#define QXTTABLEWIDGET_H

#include <QTableWidget>
#include "qxtpimpl.h"
#include "qxtglobal.h"
#include "qxttablewidgetitem.h"

class QxtTableWidgetPrivate;

class QXT_GUI_EXPORT QxtTableWidget : public QTableWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtTableWidget);
	friend class QxtTableWidgetItem;

public:
	explicit QxtTableWidget(QWidget* parent = 0);
	explicit QxtTableWidget(int rows, int columns, QWidget* parent = 0);
	virtual ~QxtTableWidget();
	
signals:
	void itemEditingStarted(QTableWidgetItem* item);
	void itemEditingFinished(QTableWidgetItem* item);
	void itemCheckStateChanged(QxtTableWidgetItem* item);
};

#endif // QXTTABLEWIDGET_H
