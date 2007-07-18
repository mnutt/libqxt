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
#ifndef QXTTOOLTIP_P_H
#define QXTTOOLTIP_P_H

#include <QPointer>
#include <QWidget>
#include <QHash>

class QVBoxLayout;

typedef QPointer<QWidget> WidgetPtr;
typedef QPair<WidgetPtr, QRect> WidgetArea;

class QxtToolTipPrivate : public QWidget
{
	Q_OBJECT

public:
	QxtToolTipPrivate();
	~QxtToolTipPrivate();

	static QxtToolTipPrivate* instance();
	void show(const QPoint& pos, QWidget* tooltip, QWidget* parent = 0, const QRect& rect = QRect());
	void setToolTip(QWidget* tooltip);
	bool eventFilter(QObject* parent, QEvent* event);
	void hideLater();
	QPoint calculatePos(int scr, const QPoint& eventPos) const;
	QHash<WidgetPtr, WidgetArea> tooltips;
	QVBoxLayout* vbox;

protected:
	void enterEvent(QEvent* event);
	void paintEvent(QPaintEvent* event);

private:
	static QxtToolTipPrivate* self;
	QWidget* currentParent;
	QRect currentRect;
};

#endif // QXTTOOLTIP_P_H
