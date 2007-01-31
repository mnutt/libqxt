/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtLabel.h"
#include <QTime>
#include <QEvent>
#include <QPainter>
#include <QFontMetrics>
#include <QApplication>

static const int Vertical_Mask = 0x02;

class QxtLabelPrivate : public QxtPrivate<QxtLabel>
{
public:
	QXT_DECLARE_PUBLIC(QxtLabel);
	
	void init(const QString& txt = QString());
	void updateLabel();
	
	QTime time;
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
    \brief A simplified label which is able to show elided and rotated text.

    QxtLabel is a simple label widget able to show elided and rotated plain text.
    In addition, QxtLabel provides a signal for clicking.

    \note Requires Qt 4.2 or newer.
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
    \fn QxtLabel::clicked()

    This signal is emitted whenever the label has been clicked.
 */

/*!
    Constructs a new QxtLabel with \a parent and \a flags.
 */
QxtLabel::QxtLabel(QWidget* parent, Qt::WindowFlags flags) : QFrame(parent, flags)
{
	QXT_INIT_PRIVATE(QxtLabel);
	qxt_d().init();
}

/*!
    Constructs a new QxtLabel with \a text, \a parent and \a flags.
 */
QxtLabel::QxtLabel(const QString& text, QWidget* parent, Qt::WindowFlags flags) : QFrame(parent, flags)
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
    \property QxtLabel::text
    \brief This property holds the text of the label
 */
QString QxtLabel::text() const
{
	return qxt_d().text;
}

void QxtLabel::setText(const QString& text)
{
	if (qxt_d().text != text)
	{
		qxt_d().text = text;
		qxt_d().updateLabel();
	}
}

/*!
    \property QxtLabel::alignment
    \brief This property holds the alignment of the text

    The text is aligned according to this property.
    The default value is \b Qt::AlignLeft|Qt::AlignTop.

    \sa text
 */
Qt::Alignment QxtLabel::alignment() const
{
	return qxt_d().align;
}

void QxtLabel::setAlignment(Qt::Alignment alignment)
{
	if (qxt_d().align != alignment)
	{
		qxt_d().align = alignment;
		update(); // no geometry change, repaint is sufficient
	}
}

/*!
    \property QxtLabel::elideMode
    \brief This property holds the elide mode of the text

    The text is elided according to this property.
    The default value is \b Qt::ElideMiddle.

    \sa text
 */
Qt::TextElideMode QxtLabel::elideMode() const
{
	return qxt_d().mode;
}

void QxtLabel::setElideMode(Qt::TextElideMode mode)
{
	if (qxt_d().mode != mode)
	{
		qxt_d().mode = mode;
		qxt_d().updateLabel();
	}
}

/*!
    \property QxtLabel::rotation
    \brief This property holds the rotation of the label

    The label is rotated according to this property.
    The default value is \b QxtLabel::NoRotation.

    \sa QxtLabel::Rotation
 */
QxtLabel::Rotation QxtLabel::rotation() const
{
	return qxt_d().rot;
}

void QxtLabel::setRotation(Rotation rotation)
{
	if (qxt_d().rot != rotation)
	{
		Rotation prev = qxt_d().rot;
		qxt_d().rot = rotation;
		switch (rotation)
		{
			case NoRotation:
			case UpsideDown:
				if (prev & Vertical_Mask)
				{
					updateGeometry();
				}
				break;
				
			case Clockwise:
			case CounterClockwise:
				if (prev & Vertical_Mask == 0)
				{
					updateGeometry();
				}
				break;
			default:
				// nothing to do
				break;
		}
	}
	update();
}

QSize QxtLabel::sizeHint() const
{
	const QFontMetrics& fm = fontMetrics();
	QSize size(fm.width(qxt_d().text), fm.height());
	if (qxt_d().rot & Vertical_Mask)
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
			if (qxt_d().rot & Vertical_Mask)
				size.transpose();
			return size;
		}
	}
}

void QxtLabel::paintEvent(QPaintEvent* event)
{
	QFrame::paintEvent(event);
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
	
	if (qxt_d().rot & Vertical_Mask)
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
	QFrame::changeEvent(event);
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

void QxtLabel::mousePressEvent(QMouseEvent* event)
{
	QFrame::mousePressEvent(event);
	qxt_d().time.start();
}

void QxtLabel::mouseReleaseEvent(QMouseEvent* event)
{
	QFrame::mouseReleaseEvent(event);
	if (qxt_d().time.elapsed() < qApp->doubleClickInterval())
		emit clicked();
}
