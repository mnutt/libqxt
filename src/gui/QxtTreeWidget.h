/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTTREEWIDGET_H
#define QXTTREEWIDGET_H

#include <QTreeWidget>
#include <QxtDefines.h>
#include <core/QxtPimpl.h>
#include <QxtItemDelegate.h>

class QxtTreeWidgetPrivate;

class QXT_DLLEXPORT QxtTreeWidget : public QTreeWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtTreeWidget);
	Q_PROPERTY(bool rootDecorated READ isRootDecorated WRITE setRootDecorated)
	Q_PROPERTY(QxtItemDelegate::DecorationStyle decorationStyle READ decorationStyle WRITE setDecorationStyle)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	
public:
	explicit QxtTreeWidget(QWidget* parent = 0);
	virtual ~QxtTreeWidget();
	
	bool isRootDecorated() const;
	void setRootDecorated(bool decorate);
	
	QxtItemDelegate::DecorationStyle decorationStyle() const;
	void setDecorationStyle(QxtItemDelegate::DecorationStyle style);
	
	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);
	
signals:
	void itemEditingStarted(QTreeWidgetItem* item);
	void itemEditingFinished(QTreeWidgetItem* item);
};

#endif // QXTTREEWIDGET_H
