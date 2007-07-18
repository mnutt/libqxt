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
#ifndef QXTLISTWIDGET_H
#define QXTLISTWIDGET_H

#include <QListWidget>
#include "qxtpimpl.h"
#include "qxtglobal.h"
#include "qxtlistwidgetitem.h"

class QxtListWidgetPrivate;

class QXT_GUI_EXPORT QxtListWidget : public QListWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtListWidget);
	friend class QxtListWidgetItem;
	
public:
	explicit QxtListWidget(QWidget* parent = 0);
	virtual ~QxtListWidget();
	
signals:
	void itemEditingStarted(QListWidgetItem* item);
	void itemEditingFinished(QListWidgetItem* item);
	void itemCheckStateChanged(QxtListWidgetItem* item);
};

#endif // QXTLISTWIDGET_H
