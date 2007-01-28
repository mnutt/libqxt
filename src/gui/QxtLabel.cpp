/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtLabel.h"
#include <QEvent>
#include <QPainter>
#include <QFontMetrics>

class QxtLabelPrivate : public QxtPrivate<QxtLabel>
{
public:
	QXT_DECLARE_PUBLIC(QxtLabel);
	
	void init(const QString& txt = QString());
	void updateLabel();
	
	QString text;
	Qt::Alignment align;
	Qt::TextElideMode mode;
	QxtLabel::Rotation rot;
};

void QxtLabelPrivate::init(const QString& txt)
{
	text = txt;
	align = Qt::AlignLeft | Qt::AlignTop;
	mode = Qt::ElideMiddle;
	rot = QxtLabel::NoRotation;
}

void QxtLabelPrivate::updateLabel()
{
	qxt_p().updateGeometry();
	qxt_p().update();
}

/*!
    \class QxtLabel QxtLabel
    \ingroup gui
    \brief A simple label which is able to show elided and rotated text.

    QxtLabel is a simple label widget able to show elided and rotated plain text.
 */

/*!
    \enum QxtLabel::Rotation

    This enum describes the rotation of the text.

    \value NoRotation        No rotation.
    \value UpsideDown        Upside down (180 degrees).
    \value Clockwise         Clockwise (90 degrees).
    \value CounterClockwise  CounterClockwise (-90 degrees).
 */

/*!
    Constructs a new QxtLabel with \a parent and \a flags.
 */
QxtLabel::QxtLabel(QWidget* parent, Qt::WindowFlags flags) : QWidget(parent, flags)
{
	QXT_INIT_PRIVATE(QxtLabel);
	qxt_d().init();
}

/*!
    Constructs a new QxtLabel with \a text, \a parent and \a flags.
 */
QxtLabel::QxtLabel(const QString& text, QWidget* parent, Qt::WindowFlags flags) : QWidget(parent, flags)
{
	QXT_INIT_PRIVATE(QxtLabel);
	qxt_d().init(text);
}

/*!
    Destructs the label.
 */
QxtLabel::~QxtLabel()
{
}

/*!
    Returns the text.

    \sa setText()
 */
QString QxtLabel::text() const
{
	return qxt_d().text;
}

/*!
    Sets the text to \a text.

    \sa text()
 */
void QxtLabel::setText(const QString& text)
{
	qxt_d().text = text;
	qxt_d().updateLabel();
}

/*!
    Returns the alignment.

    The default value of this property is Qt::AlignLeft | Qt::AlignTop.

    \sa setAlignment()
 */
Qt::Alignment QxtLabel::alignment() const
{
	return qxt_d().align;
}

/*!
    Sets the alignment to \a alignment.

    \sa alignment()
 */
void QxtLabel::setAlignment(Qt::Alignment alignment)
{
	qxt_d().align = alignment;
	update(); // no geometry change, repaint is sufficient
}

/*!
    Returns the text elide mode.

    The default value of this property is Qt::ElideMiddle.

    \sa setElideMode()
 */
Qt::TextElideMode QxtLabel::elideMode() const
{
	return qxt_d().mode;
}

/*!
    Sets the text elide mode to \a mode.

    \sa elideMode()
 */
void QxtLabel::setElideMode(Qt::TextElideMode mode)
{
	qxt_d().mode = mode;
	qxt_d().updateLabel();
}

/*!
    Returns the rotation.

    The default value of this property is QxtLabel::NoRotation.

    \sa setRotation() QxtLabel::Rotation
 */
QxtLabel::Rotation QxtLabel::rotation() const
{
	return qxt_d().rot;
}

/*!
    Sets the rotation to \a rotation.

    \sa rotation()
 */
void QxtLabel::setRotation(Rotation rotation)
{
	Rotation prev = qxt_d().rot;
	qxt_d().rot = rotation;
	switch (rotation)
	{
		case NoRotation:
		case UpsideDown:
			if (prev == Clockwise || prev == CounterClockwise)
			{
				updateGeometry();
			}
			break;
		case Clockwise:
		case CounterClockwise:
			if (prev == NoRotation || prev == UpsideDown)
			{
				updateGeometry();
			}
			break;
		default:
			// nothing to do
			break;
	}
	update();
}

QSize QxtLabel::sizeHint() const
{
	const QFontMetrics& fm = fontMetrics();
	QSize size(fm.width(qxt_d().text), fm.height());
	if (qxt_d().rot == Clockwise || qxt_d().rot == CounterClockwise)
		size.transpose();
	return size;
}

QSize QxtLabel::minimumSizeHint() const
{
	switch (qxt_d().mode)
	{
		case Qt::ElideNone:
			return sizeHint();
		default:
		{
			const QFontMetrics& fm = fontMetrics();
			QSize size(fm.width("..."), fm.height());
			if (qxt_d().rot == Clockwise || qxt_d().rot == CounterClockwise)
				size.transpose();
			return size;
		}
	}
}

void QxtLabel::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter p(this);
	p.rotate(qxt_d().rot);
	QRect r = contentsRect();
	switch (qxt_d().rot)
	{
		case UpsideDown:
			p.translate(-r.width(), -r.height());
			break;

		case Clockwise:
			p.translate(0, -r.width());
			break;
			
		case CounterClockwise:
			p.translate(-r.height(), 0);
			break;
			
		default:
			// nothing to do
			break;
	}
	
	if (qxt_d().rot == Clockwise || qxt_d().rot == CounterClockwise)
	{
		QSize s = r.size();
		s.transpose();
		r = QRect(r.topLeft(), s);
	}
	
	const QFontMetrics& fm = fontMetrics();
	p.drawText(r, qxt_d().align, fm.elidedText(qxt_d().text, qxt_d().mode, r.width()));
}

void QxtLabel::changeEvent(QEvent* event)
{
	QWidget::changeEvent(event);
	switch (event->type())
	{
		case QEvent::FontChange:
		case QEvent::ApplicationFontChange:
			qxt_d().updateLabel();
			break;
		default:
			// nothing to do
			break;
	}
}
