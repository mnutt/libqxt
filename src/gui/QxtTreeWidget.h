/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTTREEWIDGET_H
#define QXTTREEWIDGET_H

#include <QTreeWidget>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtCore/QxtPimpl>

class QxtTreeWidgetPrivate;

class QXT_GUI_EXPORT QxtTreeWidget : public QTreeWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtTreeWidget);
	Q_PROPERTY(bool rootDecorated READ isRootDecorated WRITE setRootDecorated)
	Q_PROPERTY(Qxt::DecorationStyle decorationStyle READ decorationStyle WRITE setDecorationStyle)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	
public:
	explicit QxtTreeWidget(QWidget* parent = 0);
	virtual ~QxtTreeWidget();
	
	bool isRootDecorated() const;
	void setRootDecorated(bool decorate);
	
	Qxt::DecorationStyle decorationStyle() const;
	void setDecorationStyle(Qxt::DecorationStyle style);
	
	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);
	
signals:
	void itemEditingStarted(QTreeWidgetItem* item);
	void itemEditingFinished(QTreeWidgetItem* item);
};

#endif // QXTTREEWIDGET_H
