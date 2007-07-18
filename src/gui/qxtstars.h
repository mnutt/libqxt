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
#ifndef QXTSTARS_H
#define QXTSTARS_H

#include <QAbstractSlider>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtStarsPrivate;

class QXT_GUI_EXPORT QxtStars : public QAbstractSlider
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtStars);
	Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
	Q_PROPERTY(QSize starSize READ starSize WRITE setStarSize)
	
public:
	explicit QxtStars(QWidget* parent = 0);
	virtual ~QxtStars();
	
	bool isReadOnly() const;
	void setReadOnly(bool readOnly);
	
	QSize starSize() const;
	void setStarSize(const QSize& size);
	
#ifndef QXT_DOXYGEN_RUN
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
#endif // QXT_DOXYGEN_RUN
	
#ifndef QXT_DOXYGEN_RUN
protected:
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTSTARS_H
