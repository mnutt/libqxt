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


#ifndef QXTPUSHBUTTON_H
#define QXTPUSHBUTTON_H

#include <QPushButton>
#include "qxtnamespace.h"
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtPushButtonPrivate;

class QXT_GUI_EXPORT QxtPushButton : public QPushButton
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtPushButton);
	Q_PROPERTY(Qxt::Rotation rotation READ rotation WRITE setRotation)
	Q_PROPERTY(Qt::TextFormat textFormat READ textFormat WRITE setTextFormat)
	
public:
	explicit QxtPushButton(QWidget* parent = 0);
	QxtPushButton(const QString& text, QWidget* parent = 0);
	QxtPushButton(const QIcon& icon, const QString& text, QWidget* parent = 0);
	QxtPushButton(Qxt::Rotation rotation, const QString& text, QWidget* parent = 0);
	virtual ~QxtPushButton();
	
	Qxt::Rotation rotation() const;
	void setRotation(Qxt::Rotation rotation);
	
	Qt::TextFormat textFormat() const;
	void setTextFormat(Qt::TextFormat format);
	
#ifndef QXT_DOXYGEN_RUN
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	
protected:
	virtual void paintEvent(QPaintEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTPUSHBUTTON_H
