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
#include "qxtdockwidget.h"
#include <QStyle>

class QxtDockWidgetPrivate : public QxtPrivate<QxtDockWidget>
{
public:
	QXT_DECLARE_PUBLIC(QxtDockWidget);
	
	QSize contentsSize() const;
	QSize prev;
};

QSize QxtDockWidgetPrivate::contentsSize() const
{
	QSize contents = qxt_p().size();
	int fw = qxt_p().style()->pixelMetric(QStyle::PM_DockWidgetFrameWidth);
	QSize frame(2 * fw, fw);
#ifdef Q_WS_WIN
	frame -= QSize(0, 3);
#endif
	contents -= frame;
	return contents;
}

/*!
    \class QxtDockWidget QxtDockWidget
    \ingroup gui
    \brief An extended QDockWidget that remembers its size.

    QxtDockWidget fills in the gap in QDockWidget and makes the dock
    widget to remember its size while toggling visibility off and on.

    \note 146752 - QDockWidget should remember its size when hidden/shown.<br>
    http://www.trolltech.com/developer/task-tracker/index_html?method=entry&id=146752
 */

/*!
    Constructs a new QxtDockWidget with \a title, \a parent and \a flags.
 */
QxtDockWidget::QxtDockWidget(const QString& title, QWidget* parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	QXT_INIT_PRIVATE(QxtDockWidget);
}

/*!
    Constructs a new QxtDockWidget with \a title, \a parent and \a flags.
 */
QxtDockWidget::QxtDockWidget(QWidget* parent, Qt::WindowFlags flags)
	: QDockWidget(parent, flags)
{
	QXT_INIT_PRIVATE(QxtDockWidget);
}

/*!
    Destructs the dock widget.
 */
QxtDockWidget::~QxtDockWidget()
{
}

QSize QxtDockWidget::sizeHint() const
{
	QSize size;
	if (qxt_d().prev.isValid() && !isFloating())
		size = qxt_d().prev;
	else
		size = QDockWidget::sizeHint();
	return size;
}

void QxtDockWidget::setVisible(bool visible)
{
	if (!visible && !isFloating())
		qxt_d().prev = qxt_d().contentsSize();
	QDockWidget::setVisible(visible);
}
