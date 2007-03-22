/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtPushButton.h"
#include <QStyleOptionButton>
#include <QStylePainter>
#include <QTextDocument>
#include <QMenu>

static const int Vertical_Mask = 0x02;

class QxtPushButtonPrivate : public QxtPrivate<QxtPushButton>
{
public:
	QXT_DECLARE_PUBLIC(QxtPushButton);
	QxtPushButtonPrivate();
	
	QStyleOptionButton getStyleOption() const;
	
	Qxt::Rotation rot;
	QTextDocument* doc;
	Qt::TextFormat format;
};

QxtPushButtonPrivate::QxtPushButtonPrivate() :
	rot(Qxt::NoRotation), doc(0), format(Qt::PlainText)
{
}

QStyleOptionButton QxtPushButtonPrivate::getStyleOption() const
{
	QStyleOptionButton option;
	option.initFrom(&qxt_p());
	if (rot & Vertical_Mask)
	{
		QSize size = option.rect.size();
		size.transpose();
		option.rect.setSize(size);
	}
	option.features = QStyleOptionButton::None;
	if (qxt_p().isFlat())
		option.features |= QStyleOptionButton::Flat;
	if (qxt_p().menu())
		option.features |= QStyleOptionButton::HasMenu;
	if (qxt_p().autoDefault() || qxt_p().isDefault())
		option.features |= QStyleOptionButton::AutoDefaultButton;
	if (qxt_p().isDefault())
		option.features |= QStyleOptionButton::DefaultButton;
	if (qxt_p().isDown() || (qxt_p().menu() && qxt_p().menu()->isVisible()))
		option.state |= QStyle::State_Sunken;
	if (qxt_p().isChecked())
		option.state |= QStyle::State_On;
	if (!qxt_p().isFlat() && !qxt_p().isDown())
		option.state |= QStyle::State_Raised;
	option.text = qxt_p().text();
	option.icon = qxt_p().icon();
	option.iconSize = qxt_p().iconSize();
	return option;
}

/*!
    \class QxtPushButton QxtPushButton
    \ingroup gui
    \brief A QPushButton which can be rotated.

    QxtPushButton is a QPushButton which can be rotated.

    \image html qxtpushbutton.png "QxtPushButtons in Plastique style."
 */

/*!
    Constructs a new QxtPushButton with \a parent.
 */
QxtPushButton::QxtPushButton(QWidget* parent) : QPushButton(parent)
{
	QXT_INIT_PRIVATE(QxtPushButton);
}

/*!
    Constructs a new QxtPushButton with \a text and \a parent.
 */
QxtPushButton::QxtPushButton(const QString& text, QWidget* parent) : QPushButton(text, parent)
{
	QXT_INIT_PRIVATE(QxtPushButton);
}

/*!
    Constructs a new QxtPushButton with \a icon, \a text and \a parent.
 */
QxtPushButton::QxtPushButton(const QIcon& icon, const QString& text, QWidget* parent) : QPushButton(icon, text, parent)
{
	QXT_INIT_PRIVATE(QxtPushButton);
}

/*!
    Constructs a new QxtPushButton with \a rotation, \a text and \a parent.
 */
QxtPushButton::QxtPushButton(Qxt::Rotation rotation, const QString& text, QWidget* parent) : QPushButton(text, parent)
{
	QXT_INIT_PRIVATE(QxtPushButton);
	setRotation(rotation);
}

/*!
    Destructs the button.
 */
QxtPushButton::~QxtPushButton()
{
}

/*!
    \property QxtPushButton::rotation
    \brief This property holds the rotation of the button

    The button is rotated according to this property.
    The default value is \b Qxt::NoRotation.

    \sa Qxt::Rotation
 */
Qxt::Rotation QxtPushButton::rotation() const
{
	return qxt_d().rot;
}

void QxtPushButton::setRotation(Qxt::Rotation rotation)
{
	if (qxt_d().rot != rotation)
	{
		qxt_d().rot = rotation;
		switch (rotation)
		{
			case Qxt::NoRotation:
			case Qxt::UpsideDown:
				setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
				break;
			
			case Qxt::Clockwise:
			case Qxt::CounterClockwise:
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

QString QxtPushButton::html() const
{
	return (qxt_d().doc ? qxt_d().doc->toHtml() : QString());
}

void QxtPushButton::setHtml(const QString& html)
{
	if (!qxt_d().doc)
	{
		qxt_d().doc = new QTextDocument(this);
		qxt_d().doc->setUndoRedoEnabled(false);
	}
	qxt_d().format = Qt::RichText;
	qxt_d().doc->setHtml(html);
	setText(QString());
}

/*!
    \property QxtPushButton::textFormat
    \brief This property holds the text format of the button

    Supported formats are \b Qt::PlainText and \b Qt::RichText.

    The default format is \b Qt::PlainText.
 */
Qt::TextFormat QxtPushButton::textFormat() const
{
	return qxt_d().format;
}

void QxtPushButton::setTextFormat(Qt::TextFormat format)
{
	if (qxt_d().format != format)
	{
		qxt_d().format = format;
		switch (format)
		{
			case Qt::RichText:
				setHtml(text());
				break;

			case Qt::PlainText:
			default:
				qxt_d().format = Qt::PlainText;
				if (qxt_d().doc)
				{
					setText(qxt_d().doc->toPlainText());
					delete qxt_d().doc;
					qxt_d().doc = 0;
				}
				break;
		}
	}
}

QSize QxtPushButton::sizeHint() const
{
	QSize size;
	switch (qxt_d().format)
	{
		case Qt::RichText:
			if (qxt_d().doc)
			{
				size = qxt_d().doc->size().toSize();
				break;
			} // intentional fall through if (doc == 0)

		case Qt::PlainText:
		default:
			size = QPushButton::sizeHint();
			break;
	}

	if (qxt_d().rot & Vertical_Mask)
		size.transpose();

	return size;
}

QSize QxtPushButton::minimumSizeHint() const
{
	QSize size;
	switch (qxt_d().format)
	{
		case Qt::RichText:
			if (qxt_d().doc)
			{
				size = qxt_d().doc->size().toSize();
				break;
			} // intentional fall through if (doc == 0)

		case Qt::PlainText:
		default:
			size = QPushButton::minimumSizeHint();
			break;
	}
	
	if (qxt_d().rot & Vertical_Mask)
		size.transpose();

	return size;
}

void QxtPushButton::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	
	if (qxt_d().format == Qt::RichText && !text().isEmpty())
		setHtml(text());
	
	QStylePainter painter(this);
	painter.rotate(qxt_d().rot);
	switch (qxt_d().rot)
	{
		case Qxt::UpsideDown:
			painter.translate(-width(), -height());
			break;

		case Qxt::Clockwise:
			painter.translate(0, -width());
			break;
			
		case Qxt::CounterClockwise:
			painter.translate(-height(), 0);
			break;
			
		default:
			// nothing to do
			break;
	}
	
	painter.drawControl(QStyle::CE_PushButton, qxt_d().getStyleOption());
	
	if (qxt_d().format == Qt::RichText)
	{
		if (qxt_d().doc)
		{
			//QRect area = contentsRect();
			//area.setSize(qxt_d().doc->size().toSize());
			//area.moveCenter(contentsRect()().center());
			//qxt_d().doc->drawContents(&painter, area);
			painter.translate((width() - qxt_d().doc->size().width()) / 2,
					  (height() - qxt_d().doc->size().height()) / 2);
			qxt_d().doc->drawContents(&painter, contentsRect());
		}
	}
}
