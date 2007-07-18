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
#ifndef QXTSPANSLIDER_P_H
#define QXTSPANSLIDER_P_H

#include <QStyle>
#include <QObject>
#include "qxtspanslider.h"
#include "qxtpimpl.h"

class QStylePainter;
class QStyleOptionSlider;

class QxtSpanSliderPrivate : public QObject, public QxtPrivate<QxtSpanSlider>
{
	Q_OBJECT
	
public:
	QXT_DECLARE_PUBLIC(QxtSpanSlider);
	
	enum SpanHandle
	{
		NoHandle,
		LowerHandle,
		UpperHandle
	};
	
	QxtSpanSliderPrivate();
	void initStyleOption(QStyleOptionSlider* option, SpanHandle handle = UpperHandle) const;
	int pick(const QPoint& pt) const { return qxt_p().orientation() == Qt::Horizontal ? pt.x() : pt.y(); }
	int pixelPosToRangeValue(int pos) const;
	void handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, SpanHandle handle);
	void drawHandle(QStylePainter* painter, SpanHandle handle) const;
	void setupPainter(QPainter* painter, Qt::Orientation orientation, qreal x1, qreal y1, qreal x2, qreal y2) const;
	void drawSpan(QStylePainter* painter, const QRect& rect) const;
	void triggerAction(QAbstractSlider::SliderAction action, bool main);
	void swapControls();
	
	int lower;
	int upper;
	int offset;
	int position;
	SpanHandle lastPressed;
	SpanHandle mainControl;
	QStyle::SubControl lowerPressed;
	QStyle::SubControl upperPressed;
	
public slots:
	void updateRange(int min, int max);
};

#endif // QXTSPANSLIDER_P_H
