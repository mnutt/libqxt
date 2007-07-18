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
#ifndef QXTTOOLTIP_H
#define QXTTOOLTIP_H

#include <QRect>
#include <QPointer>
#include "qxtglobal.h"

class QWidget;

class QXT_GUI_EXPORT QxtToolTip
{
#ifndef QXT_DOXYGEN_RUN
	explicit QxtToolTip() {}
#endif // QXT_DOXYGEN_RUN

public:
	static void show(const QPoint& pos, QWidget* tooltip, QWidget* parent = 0, const QRect& rect = QRect());
	static void hide();

	static QWidget* toolTip(QWidget* parent);
	static void setToolTip(QWidget* parent, QWidget* tooltip, const QRect& rect = QRect());

	static QRect toolTipRect(QWidget* parent);
	static void setToolTipRect(QWidget* parent, const QRect& rect);

	static int margin();
	static void setMargin(int margin);

	static qreal opacity();
	static void setOpacity(qreal level);
};

inline uint qHash(const QPointer<QWidget> key)
{
	return reinterpret_cast<quint64>(key ? (&*key) : 0);
}

#endif // QXTTOOLTIP_H
