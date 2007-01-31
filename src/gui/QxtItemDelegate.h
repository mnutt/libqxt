/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTITEMDELEGATE_H
#define QXTITEMDELEGATE_H

#include <QItemDelegate>
#include <QxtDefines.h>
#include <core/QxtPimpl.h>

class QxtItemDelegatePrivate;

class QXT_DLLEXPORT QxtItemDelegate : public QItemDelegate
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtItemDelegate);
	Q_PROPERTY(bool rootDecorated READ isRootDecorated WRITE setRootDecorated)
	Q_PROPERTY(DecorationStyle decorationStyle READ decorationStyle WRITE setDecorationStyle)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	Q_ENUMS(DecorationStyle)
	
public:
	enum DecorationStyle
	{
		Buttonlike,
		Menulike
		// TODO: invent a few more of these..
	};
	
	explicit QxtItemDelegate(QObject* parent = 0);
	virtual ~QxtItemDelegate();
	
	bool isRootDecorated() const;
	void setRootDecorated(bool decorate);
	
	DecorationStyle decorationStyle() const;
	void setDecorationStyle(DecorationStyle style);
	
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
