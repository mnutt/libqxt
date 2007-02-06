/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTTABWIDGET_H
#define QXTTABWIDGET_H

#include <QTabWidget>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtCore/QxtPimpl>

class QxtTabWidgetPrivate;

class QXT_GUI_EXPORT QxtTabWidget : public QTabWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtTabWidget);
	Q_PROPERTY(Qt::ContextMenuPolicy tabContextMenuPolicy READ tabContextMenuPolicy WRITE setTabContextMenuPolicy)
	
public:
	explicit QxtTabWidget(QWidget* parent = 0);
	virtual ~QxtTabWidget();
	
	Qt::ContextMenuPolicy tabContextMenuPolicy() const;
	void setTabContextMenuPolicy(Qt::ContextMenuPolicy policy);
	
	void addTabAction(int index, QAction* action);
	void addTabActions(int index, QList<QAction*> actions);
	void clearTabActions(int index);
	void insertTabAction(int index, QAction* before, QAction* action);
	void insertTabActions(int index, QAction* before, QList<QAction*> actions);
	void removeTabAction(int index, QAction* action);
	QList<QAction*> tabActions(int index) const;
	
signals:
	void tabContextMenuRequested(int index, const QPoint& globalPos);
	
protected:
	virtual void tabInserted(int index);
	virtual void tabRemoved(int index);
	
	virtual void contextMenuEvent(QContextMenuEvent* event);
	virtual void tabContextMenuEvent(int index, QContextMenuEvent* event);
};

#endif // QXTQXTTABWIDGET_H
