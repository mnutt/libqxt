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
#include <QxtPimpl.h>
#include "QxtTreeWidgetItem.h"

class QxtTreeWidgetPrivate;

class QXT_GUI_EXPORT QxtTreeWidget : public QTreeWidget
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtTreeWidget);
	Q_PROPERTY(bool branchesDrawn READ branchesDrawn WRITE setBranchesDrawn)
	Q_PROPERTY(Qxt::DecorationStyle decorationStyle READ decorationStyle WRITE setDecorationStyle)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	friend class QxtTreeWidgetItem;
	
public:
	explicit QxtTreeWidget(QWidget* parent = 0);
	virtual ~QxtTreeWidget();
	
	bool branchesDrawn() const;
	void setBranchesDrawn(bool draw);
	
	Qxt::DecorationStyle decorationStyle() const;
	void setDecorationStyle(Qxt::DecorationStyle style);
	
	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);
	
signals:
	void itemEditingStarted(QTreeWidgetItem* item);
	void itemEditingFinished(QTreeWidgetItem* item);
	void itemCheckStateChanged(QxtTreeWidgetItem* item);
	
#ifndef QXT_DOXYGEN_RUN
protected:
	void drawBranches(QPainter* painter, const QRect& rect, const QModelIndex& index) const;
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTTREEWIDGET_H
