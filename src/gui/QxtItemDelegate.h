/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTITEMDELEGATE_H
#define QXTITEMDELEGATE_H

#include <QItemDelegate>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtCore/QxtPimpl>

class QxtItemDelegatePrivate;

class QXT_GUI_EXPORT QxtItemDelegate : public QItemDelegate
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtItemDelegate);
	Q_PROPERTY(bool rootDecorated READ isRootDecorated WRITE setRootDecorated)
	Q_PROPERTY(Qxt::DecorationStyle decorationStyle READ decorationStyle WRITE setDecorationStyle)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	
public:
	explicit QxtItemDelegate(QObject* parent = 0);
	virtual ~QxtItemDelegate();
	
	bool isRootDecorated() const;
	void setRootDecorated(bool decorate);
	
	Qxt::DecorationStyle decorationStyle() const;
	void setDecorationStyle(Qxt::DecorationStyle style);
	
	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);
	
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
	
	virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
	
signals:
	void editingStarted(const QModelIndex& index);
	void editingFinished(const QModelIndex& index);
};

#endif // QXTITEMDELEGATE_H
