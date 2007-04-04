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


#ifndef QXTITEMDELEGATE_H
#define QXTITEMDELEGATE_H

#include <QItemDelegate>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtPimpl.h>

class QxtItemDelegatePrivate;

class QXT_GUI_EXPORT QxtItemDelegate : public QItemDelegate
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtItemDelegate);
	Q_PROPERTY(Qxt::DecorationStyle decorationStyle READ decorationStyle WRITE setDecorationStyle)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	
public:
	explicit QxtItemDelegate(QObject* parent = 0);
	virtual ~QxtItemDelegate();
	
	Qxt::DecorationStyle decorationStyle() const;
	void setDecorationStyle(Qxt::DecorationStyle style);
	
	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);
	
#ifndef QXT_DOXYGEN_RUN
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
	
	virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
#endif // QXT_DOXYGEN_RUN
	
signals:
	void editingStarted(const QModelIndex& index);
	void editingFinished(const QModelIndex& index);
};

#endif // QXTITEMDELEGATE_H
