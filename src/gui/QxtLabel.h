/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTLABEL_H
#define QXTLABEL_H

#include <QFrame>
#include <QxtDefines.h>
#include <core/QxtPimpl.h>

class QxtLabelPrivate;

class QXT_DLLEXPORT QxtLabel : public QFrame
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtLabel);
	Q_PROPERTY(QString text READ text WRITE setText)
	Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	Q_PROPERTY(Rotation rotation READ rotation WRITE setRotation)
	Q_ENUMS(Rotation)
	
public:
	// TODO: merge this with QxtPushButton::Rotation
	//       (maybe something similar than qnamespace.h)
	enum Rotation
	{
		NoRotation		= 0,
		UpsideDown		= 180,
		Clockwise		= 90,
		CounterClockwise	= 270
	};
	
	explicit QxtLabel(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	QxtLabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags flags = 0);
	virtual ~QxtLabel();
	
	QString text() const;
	void setText(const QString& text);
	
	Qt::Alignment alignment() const;
	void setAlignment(Qt::Alignment alignment);
	
	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);
	
	Rotation rotation() const;
	void setRotation(Rotation rotation);
	
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	
signals:
	void clicked();
	
protected:
	virtual void changeEvent(QEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
};

#endif // QXTLABEL_H
