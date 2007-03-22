/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTPUSHBUTTON_H
#define QXTPUSHBUTTON_H

#include <QPushButton>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtPimpl.h>

class QxtPushButtonPrivate;

class QXT_GUI_EXPORT QxtPushButton : public QPushButton
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtPushButton);
	Q_PROPERTY(Qxt::Rotation rotation READ rotation WRITE setRotation)
	
public:
	explicit QxtPushButton(QWidget* parent = 0);
	QxtPushButton(const QString& text, QWidget* parent = 0);
	QxtPushButton(const QIcon& icon, const QString& text, QWidget* parent = 0);
	QxtPushButton(Qxt::Rotation rotation, const QString& text, QWidget* parent = 0);
	virtual ~QxtPushButton();
	
	Qxt::Rotation rotation() const;
	void setRotation(Qxt::Rotation rotation);

	Qt::TextFormat textFormat() const;
	void setTextFormat(Qt::TextFormat format);
	
#ifndef QXT_DOXYGEN_RUN
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	
protected:
	virtual void paintEvent(QPaintEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTPUSHBUTTON_H
