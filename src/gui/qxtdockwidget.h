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
#ifndef QXTDOCKWIDGET_H
#define QXTDOCKWIDGET_H

#include <QDockWidget>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtDockWidgetPrivate;

class QXT_GUI_EXPORT QxtDockWidget : public QDockWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtDockWidget);

public:
	explicit QxtDockWidget(const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0);
	explicit QxtDockWidget(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	virtual ~QxtDockWidget();

#ifndef QXT_DOXYGEN_RUN
	QSize sizeHint() const;
	void setVisible(bool visible);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTDOCKWIDGET_H
