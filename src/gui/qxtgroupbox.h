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
#ifndef QXTGROUPBOX_H
#define QXTGROUPBOX_H

#include <QGroupBox>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtGroupBoxPrivate;

class QXT_GUI_EXPORT QxtGroupBox : public QGroupBox
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtGroupBox);
	Q_PROPERTY(bool collapsive READ isCollapsive WRITE setCollapsive)
	
public:
	explicit QxtGroupBox(QWidget* parent = 0);
	explicit QxtGroupBox(const QString& title, QWidget* parent = 0);
	virtual ~QxtGroupBox();
	
	bool isCollapsive() const;
	void setCollapsive(bool enabled);
	
public slots:
	void setCollapsed(bool collapsed = true);
	void setExpanded(bool expanded = true);
	
#ifndef QXT_DOXYGEN_RUN
protected:
	virtual void childEvent(QChildEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTGROUPBOX_H
