/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTSPANSLIDER_H
#define QXTSPANSLIDER_H

#include <QSlider>
#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>
#include <QxtPimpl.h>

class QxtSpanSliderPrivate;

class QXT_GUI_EXPORT QxtSpanSlider : public QSlider
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtSpanSlider);
	Q_PROPERTY(int lower READ lower WRITE setLower)
	Q_PROPERTY(int upper READ upper WRITE setUpper)
	
public:
	explicit QxtSpanSlider(QWidget* parent = 0);
	QxtSpanSlider(Qt::Orientation orientation, QWidget* parent = 0);
	virtual ~QxtSpanSlider();
	
	int lower() const;
	int upper() const;
	
public slots:
	void setLower(int lower);
	void setUpper(int upper);
	void setSpan(int lower, int upper);
	
signals:
	void spanChanged(int lower, int upper);
	void lowerChanged(int lower);
	void upperChanged(int upper);
	
#ifndef QXT_DOXYGEN_RUN
protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTSPANSLIDER_H
