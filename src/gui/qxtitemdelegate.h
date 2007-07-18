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
#ifndef QXTITEMDELEGATE_H
#define QXTITEMDELEGATE_H

#include <QItemDelegate>
#include "qxtglobal.h"
#include "qxtnamespace.h"
#include "qxtpimpl.h"

class QxtItemDelegatePrivate;

class QXT_GUI_EXPORT QxtItemDelegate : public QItemDelegate
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtItemDelegate);
	Q_PROPERTY(Qxt::DecorationStyle decorationStyle READ decorationStyle WRITE setDecorationStyle)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	Q_PROPERTY(QString progressTextFormat READ progressTextFormat WRITE setProgressTextFormat)
	Q_PROPERTY(bool progressTextVisible READ isProgressTextVisible WRITE setProgressTextVisible)

public:
	explicit QxtItemDelegate(QObject* parent = 0);
	virtual ~QxtItemDelegate();

	enum { ProgressRole = Qt::UserRole + 328 };

	Qxt::DecorationStyle decorationStyle() const;
	void setDecorationStyle(Qxt::DecorationStyle style);

	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);

	QString progressTextFormat() const;
	void setProgressTextFormat(const QString& format);

	bool isProgressTextVisible() const;
	void setProgressTextVisible(bool visible);

#ifndef QXT_DOXYGEN_RUN
	virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

	virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
#endif // QXT_DOXYGEN_RUN

signals:
	void editingStarted(const QModelIndex& index);
	void editingFinished(const QModelIndex& index);
};

#endif // QXTITEMDELEGATE_H
