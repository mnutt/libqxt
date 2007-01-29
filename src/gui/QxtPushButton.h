/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTPUSHBUTTON_H
#define QXTPUSHBUTTON_H

#include <QPushButton>
#include <QxtDefines.h>
#include <core/QxtPimpl.h>

class QxtPushButtonPrivate;

class QXT_DLLEXPORT QxtPushButton : public QPushButton
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtPushButton);
	Q_PROPERTY(Rotation rotation READ rotation WRITE setRotation)
	Q_ENUMS(Rotation)
	
public:
	// TODO: merge this with QxtLabel::Rotation
	//       (maybe something similar than qnamespace.h)
	enum Rotation
	{
		NoRotation		= 0,
		UpsideDown		= 180,
		Clockwise		= 90,
		CounterClockwise	= 270
	};
	
	explicit QxtPushButton(QWidget* parent = 0);
	QxtPushButton(const QString& text, QWidget* parent = 0);
	QxtPushButton(const QIcon& icon, const QString& text, QWidget* parent = 0);
	virtual ~QxtPushButton();
	
	Rotation rotation() const;
	void setRotation(Rotation rotation);
	
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	
protected:
	virtual void paintEvent(QPaintEvent* event);
};

#endif // QXTPUSHBUTTON_H
