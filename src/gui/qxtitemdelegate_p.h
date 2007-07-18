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
#ifndef QXTITEMDELEGATE_P_H
#define QXTITEMDELEGATE_P_H

#include "qxtpimpl.h"
#include "qxtitemdelegate.h"
#include <QPersistentModelIndex>
#include <QPointer>

class QPainter;
class QTreeView;

class QxtItemDelegatePrivate : public QObject, public QxtPrivate<QxtItemDelegate>
{
	Q_OBJECT
	
public:
	QXT_DECLARE_PUBLIC(QxtItemDelegate);
	QxtItemDelegatePrivate();

	void paintButton(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const;
	void paintMenu(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, const QTreeView* view) const;
	void paintProgress(QPainter* painter, const QStyleOptionViewItem& option, int progress) const;
	void setCurrentEditor(QWidget* editor, const QModelIndex& index) const;
	
	bool textVisible;
	QString progressFormat;
	Qt::TextElideMode elide;
	Qxt::DecorationStyle style;
	mutable QPointer<QWidget> currentEditor;
	mutable QPersistentModelIndex currentEdited;
	
private slots:
	void closeEditor(QWidget* editor);
};

#endif // QXTITEMDELEGATE_P_H
