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


#ifndef QXTSPANSLIDER_H
#define QXTSPANSLIDER_H

#include <QSlider>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtPimpl.h>

class QxtSpanSliderPrivate;

class QXT_GUI_EXPORT QxtSpanSlider : public QSlider
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtSpanSlider);
	Q_PROPERTY(int lower READ lower WRITE setLower)
	Q_PROPERTY(int upper READ upper WRITE setUpper)
	
public:
	explicit QxtSpanSlider(QWidget* parent = 0);
	QxtSpanSlider(Qt::Orientation orientation, QWidget* parent = 0);
	virtual ~QxtSpanSlider();
	
	int lower() const;
	int upper() const;
	
public slots:
	void setLower(int lower);
	void setUpper(int upper);
	void setSpan(int lower, int upper);
	
signals:
	void spanChanged(int lower, int upper);
	void lowerChanged(int lower);
	void upperChanged(int upper);
	
#ifndef QXT_DOXYGEN_RUN
protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTSPANSLIDER_H
