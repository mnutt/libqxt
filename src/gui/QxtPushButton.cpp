/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtPushButton.h"
#include <QMenu>
#include <QStylePainter>
#include <QStyleOptionButton>

static const int Vertical_Mask = 0x02;

class QxtPushButtonPrivate : public QxtPrivate<QxtPushButton>
{
public:
	QXT_DECLARE_PUBLIC(QxtPushButton);
	
	void init();
	QStyleOptionButton getStyleOption() const;
	
	QxtPushButton::Rotation rot;
};

void QxtPushButtonPrivate::init()
{
	rot = QxtPushButton::NoRotation;
}

// borrowed from qpushbutton.h (get rid of this in Qt 4.3)
QStyleOptionButton QxtPushButtonPrivate::getStyleOption() const
{
	QStyleOptionButton opt;
	opt.initFrom(&qxt_p());
	if (rot & Vertical_Mask)
	{
		QSize size = opt.rect.size();
		size.transpose();
		opt.rect.setSize(size);
	}
	opt.features = QStyleOptionButton::None;
	if (qxt_p().isFlat())
		opt.features |= QStyleOptionButton::Flat;
	if (qxt_p().menu())
		opt.features |= QStyleOptionButton::HasMenu;
	if (qxt_p().autoDefault() || qxt_p().isDefault())
		opt.features |= QStyleOptionButton::AutoDefaultButton;
	if (qxt_p().isDefault())
		opt.features |= QStyleOptionButton::DefaultButton;
	if (qxt_p().isDown() || (qxt_p().menu() && qxt_p().menu()->isVisible()))
		opt.state |= QStyle::State_Sunken;
	if (qxt_p().isChecked())
		opt.state |= QStyle::State_On;
	if (!qxt_p().isFlat() && !qxt_p().isDown())
		opt.state |= QStyle::State_Raised;
	opt.text = qxt_p().text();
	opt.icon = qxt_p().icon();
	opt.iconSize = qxt_p().iconSize();
	return opt;
}

/*!
    \class QxtPushButton QxtPushButton
    \ingroup gui
    \brief A simple push button which can be rotated.

    QxtPushButton is a simple push button widget which can be rotated.
 */

/*!
    \enum QxtPushButton::Rotation

    This enum describes the rotation of the text.

    \value NoRotation        No rotation.
    \value UpsideDown        Upside down (180 degrees).
    \value Clockwise         Clockwise (90 degrees).
    \value CounterClockwise  CounterClockwise (-90 degrees).
 */

/*!
    Constructs a new QxtPushButton with \a parent.
 */
QxtPushButton::QxtPushButton(QWidget* parent) : QPushButton(parent)
{
	QXT_INIT_PRIVATE(QxtPushButton);
	qxt_d().init();
}

/*!
    Constructs a new QxtPushButton with \a text and \a parent.
 */
QxtPushButton::QxtPushButton(const QString& text, QWidget* parent) : QPushButton(text, parent)
{
	QXT_INIT_PRIVATE(QxtPushButton);
	qxt_d().init();
}

/*!
    Constructs a new QxtPushButton with \a icon, \a text and \a parent.
 */
QxtPushButton::QxtPushButton(const QIcon& icon, const QString& text, QWidget* parent) : QPushButton(icon, text, parent)
{
	QXT_INIT_PRIVATE(QxtPushButton);
	qxt_d().init();
}

/*!
    Destructs the button.
 */
QxtPushButton::~QxtPushButton()
{
}

/*!
    Returns the rotation.

    The default value of this property is QxtPushButton::NoRotation.

    \sa setRotation() QxtPushButton::Rotation
 */
QxtPushButton::Rotation QxtPushButton::rotation() const
{
	return qxt_d().rot;
}

/*!
    Sets the rotation to \a rotation.

    \sa rotation()
 */
void QxtPushButton::setRotation(Rotation rotation)
{
	if (qxt_d().rot != rotation)
	{
		qxt_d().rot = rotation;
		switch (rotation)
		{
			case NoRotation:
			case UpsideDown:
				setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
				break;
			
			case Clockwise:
			case CounterClockwise:
				setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
				break;
			
			default:
				// nothing to do
				break;
		}
		updateGeometry();
		update();
	}
}

QSize QxtPushButton::sizeHint() const
{
	QSize size = QPushButton::sizeHint();
	if (qxt_d().rot & Vertical_Mask)
		size.transpose();
	return size;
}

QSize QxtPushButton::minimumSizeHint() const
{
	QSize size = QPushButton::minimumSizeHint();
	if (qxt_d().rot & Vertical_Mask)
		size.transpose();
	return size;
}

void QxtPushButton::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QStylePainter painter(this);
	painter.rotate(qxt_d().rot);
	switch (qxt_d().rot)
	{
		case UpsideDown:
			painter.translate(-width(), -height());
			break;

		case Clockwise:
			painter.translate(0, -width());
			break;
			
		case CounterClockwise:
			painter.translate(-height(), 0);
			break;
			
		default:
			// nothing to do
			break;
	}
	
	painter.drawControl(QStyle::CE_PushButton, qxt_d().getStyleOption());
}
