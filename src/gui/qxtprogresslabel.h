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
#ifndef QXTPROGRESSLABEL_H
#define QXTPROGRESSLABEL_H

#include <QLabel>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtProgressLabelPrivate;

class QXT_GUI_EXPORT QxtProgressLabel : public QLabel
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtProgressLabel);
	Q_PROPERTY(QString contentFormat READ contentFormat WRITE setContentFormat)
	Q_PROPERTY(QString timeFormat READ timeFormat WRITE setTimeFormat)
	Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval)
	
public:
	explicit QxtProgressLabel(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	explicit QxtProgressLabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags flags = 0);
	virtual ~QxtProgressLabel();
	
	QString contentFormat() const;
	void setContentFormat(const QString& format);
	
	QString timeFormat() const;
	void setTimeFormat(const QString& format);
	
	int updateInterval() const;
	void setUpdateInterval(int msecs);
	
public slots:
	void setValue(int value);
	void refresh();
	void restart();
	
#ifndef QXT_DOXYGEN_RUN
	virtual void timerEvent(QTimerEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTPROGRESSLABEL_H
