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
#ifndef QXTTABLEWIDGETITEM_H
#define QXTTABLEWIDGETITEM_H

#include <QTableWidgetItem>
#include "qxtnamespace.h"
#include "qxtglobal.h"

class QXT_GUI_EXPORT QxtTableWidgetItem : public QTableWidgetItem
{
public:
	explicit QxtTableWidgetItem(int type = Type);
	explicit QxtTableWidgetItem(const QString& text, int type = Type);
	explicit QxtTableWidgetItem(const QIcon& icon, const QString& text, int type = Type);
	explicit QxtTableWidgetItem(const QTableWidgetItem& other);
	virtual ~QxtTableWidgetItem();
	
	bool testFlag(Qt::ItemFlag flag) const;
	void setFlag(Qt::ItemFlag flag, bool enabled = true);
	
#ifndef QXT_DOXYGEN_RUN
	virtual void setData(int role, const QVariant& value);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTTABLEWIDGETITEM_H
