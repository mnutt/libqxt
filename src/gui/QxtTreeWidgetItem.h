/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTTREEWIDGETITEM_H
#define QXTTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

class QXT_GUI_EXPORT QxtTreeWidgetItem : public QTreeWidgetItem
{
public:
	explicit QxtTreeWidgetItem(int type = Type);
	QxtTreeWidgetItem(const QStringList& strings, int type = Type);
	QxtTreeWidgetItem(QTreeWidget* parent, int type = Type);
	QxtTreeWidgetItem(QTreeWidget* parent, const QStringList& strings, int type = Type);
	QxtTreeWidgetItem(QTreeWidget* parent, QTreeWidgetItem* preceding, int type = Type);
	QxtTreeWidgetItem(QTreeWidgetItem* parent, int type = Type);
	QxtTreeWidgetItem(QTreeWidgetItem* parent, const QStringList& strings, int type = Type);
	QxtTreeWidgetItem(QTreeWidgetItem* parent, QTreeWidgetItem* preceding, int type = Type);
	QxtTreeWidgetItem(const QxtTreeWidgetItem& other);
	virtual ~QxtTreeWidgetItem();
	
	virtual void setData(int column, int role, const QVariant& value);
};

#endif // QXTTREEWIDGET_H
