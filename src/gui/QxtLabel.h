/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTLABEL_H
#define QXTLABEL_H

#include <QFrame>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtPimpl.h>

class QxtLabelPrivate;

class QXT_GUI_EXPORT QxtLabel : public QFrame
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtLabel);
	Q_PROPERTY(QString text READ text WRITE setText)
	Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
	Q_PROPERTY(Qt::TextElideMode elideMode READ elideMode WRITE setElideMode)
	Q_PROPERTY(Qxt::Rotation rotation READ rotation WRITE setRotation)
	
public:
	explicit QxtLabel(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	QxtLabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags flags = 0);
	virtual ~QxtLabel();
	
	QString text() const;
	void setText(const QString& text);
	
	Qt::Alignment alignment() const;
	void setAlignment(Qt::Alignment alignment);
	
	Qt::TextElideMode elideMode() const;
	void setElideMode(Qt::TextElideMode mode);
	
	Qxt::Rotation rotation() const;
	void setRotation(Qxt::Rotation rotation);
	
#ifndef QXT_DOXYGEN_RUN
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
#endif // QXT_DOXYGEN_RUN
	
signals:
	void clicked();
	
#ifndef QXT_DOXYGEN_RUN
protected:
	virtual void changeEvent(QEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTLABEL_H
