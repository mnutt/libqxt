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
#ifndef QXTLISTWIDGETITEM_H
#define QXTLISTWIDGETITEM_H

#include <QListWidgetItem>
#include "qxtnamespace.h"
#include "qxtglobal.h"

class QXT_GUI_EXPORT QxtListWidgetItem : public QListWidgetItem
{
public:
	explicit QxtListWidgetItem(QListWidget* parent = 0, int type = Type);
	explicit QxtListWidgetItem(const QString& text, QListWidget* parent = 0, int type = Type);
	explicit QxtListWidgetItem(const QIcon& icon, const QString& text, QListWidget* parent = 0, int type = Type);
	explicit QxtListWidgetItem(const QxtListWidgetItem& other);
	virtual ~QxtListWidgetItem();
	
	bool testFlag(Qt::ItemFlag flag) const;
	void setFlag(Qt::ItemFlag flag, bool enabled = true);
	
#ifndef QXT_DOXYGEN_RUN
	virtual void setData(int role, const QVariant& value);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTLISTWIDGETITEM_H
