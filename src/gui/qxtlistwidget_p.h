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
#ifndef QXTLISTWIDGET_P_H
#define QXTLISTWIDGET_P_H

#include "qxtpimpl.h"
#include "qxtlistwidget.h"

class QxtItemDelegate;

class QxtListWidgetPrivate : public QObject, public QxtPrivate<QxtListWidget>
{
	Q_OBJECT
public:
	QXT_DECLARE_PUBLIC(QxtListWidget);
	QxtListWidgetPrivate();
	
private slots:
	void informStartEditing(const QModelIndex& index);
	void informFinishEditing(const QModelIndex& index);
};

#endif // QXTLISTWIDGET_P_H
