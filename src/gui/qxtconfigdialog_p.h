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
#ifndef QXTCONFIGDIALOG_P_H
#define QXTCONFIGDIALOG_P_H

#include "qxtpimpl.h"
#include "qxtconfigdialog.h"
#include <QItemDelegate>
#include <QListWidget>

class QGridLayout;
class QStackedWidget;
class QDialogButtonBox;

class QxtConfigListWidget : public QListWidget
{
public:
	QxtConfigListWidget(QWidget* parent = 0);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void invalidate();
	
	bool hasHoverEffect() const;
	void setHoverEffect(bool enabled);

protected:
	void scrollContentsBy(int dx, int dy);

private:
	mutable QSize hint;
};

class QxtConfigDelegate : public QItemDelegate
{
public:
	QxtConfigDelegate(QObject* parent = 0);
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	bool hover;
};

class QxtConfigDialogPrivate : public QObject, public QxtPrivate<QxtConfigDialog>
{
	Q_OBJECT

public:
	QXT_DECLARE_PUBLIC(QxtConfigDialog);

	void init(QxtConfigDialog::IconPosition position = QxtConfigDialog::West);
	void initList();
	void relayout();

	QGridLayout* grid;
	QStackedWidget* stack;
	QxtConfigListWidget* list;
#if QT_VERSION >= 0x040200
	QDialogButtonBox* buttons;
#else // QT_VERSION >= 0x040200
	QWidget* buttons;
#endif // QT_VERSION
	QxtConfigDialog::IconPosition pos;
};

#endif // QXTCONFIGDIALOG_P_H
