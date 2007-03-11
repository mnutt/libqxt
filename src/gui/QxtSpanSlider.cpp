/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtSpanSlider.h"
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionSlider>

class QxtSpanSliderPrivate : public QxtPrivate<QxtSpanSlider>
{
public:
	QXT_DECLARE_PUBLIC(QxtSpanSlider);
	
	enum SpanHandle
	{
		LowerHandle,
		UpperHandle
	};
	
	void initStyleOption(QStyleOptionSlider* option, SpanHandle handle = UpperHandle) const;
	int pick(const QPoint& pt) const { return qxt_p().orientation() == Qt::Horizontal ? pt.x() : pt.y(); }
	int pixelPosToRangeValue(int pos) const;
	void handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, SpanHandle handle);
	void drawHandle(QStylePainter* painter, SpanHandle handle) const;
	void drawSpan(QStylePainter* painter, const QRect& rect) const;
	
	int lower;
	int upper;
	int offset;
	int position;
	QStyle::SubControl lowerPressed;
	QStyle::SubControl upperPressed;
};

// TODO: get rid of this in Qt 4.3
void QxtSpanSliderPrivate::initStyleOption(QStyleOptionSlider* option, SpanHandle handle) const
{
	if (!option)
		return;
	
	const QSlider* p = &qxt_p();
	option->initFrom(p);
	option->subControls = QStyle::SC_None;
	option->activeSubControls = QStyle::SC_None;
	option->orientation = p->orientation();
	option->maximum = p->maximum();
	option->minimum = p->minimum();
	option->tickPosition = p->tickPosition();
	option->tickInterval = p->tickInterval();
	option->upsideDown = (p->orientation() == Qt::Horizontal) ?
			(p->invertedAppearance() != (option->direction == Qt::RightToLeft)) : (!p->invertedAppearance());
	option->direction = Qt::LeftToRight; // we use the upsideDown option instead
	option->sliderPosition = (handle == LowerHandle ? lower : upper);
	option->sliderValue = (handle == LowerHandle ? lower : upper);
	option->singleStep = p->singleStep();
	option->pageStep = p->pageStep();
	if (p->orientation() == Qt::Horizontal)
		option->state |= QStyle::State_Horizontal;
}

int QxtSpanSliderPrivate::pixelPosToRangeValue(int pos) const
{
	QStyleOptionSlider opt;
	initStyleOption(&opt);
	
	int sliderMin = 0;
	int sliderMax = 0;
	int sliderLength = 0;
	const QSlider* p = &qxt_p();
	const QRect gr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, p);
	const QRect sr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, p);
	if (p->orientation() == Qt::Horizontal)
	{
		sliderLength = sr.width();
		sliderMin = gr.x();
		sliderMax = gr.right() - sliderLength + 1;
	}
	else
	{
		sliderLength = sr.height();
		sliderMin = gr.y();
		sliderMax = gr.bottom() - sliderLength + 1;
	}
	return QStyle::sliderValueFromPosition(p->minimum(), p->maximum(), pos - sliderMin,
					       sliderMax - sliderMin, opt.upsideDown);
}

void QxtSpanSliderPrivate::handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, SpanHandle handle)
{
	QStyleOptionSlider opt;
	initStyleOption(&opt, handle);
	QSlider* p = &qxt_p();
	const QStyle::SubControl oldControl = control;
	control = p->style()->hitTestComplexControl(QStyle::CC_Slider, &opt, pos, p);
	const QRect sr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, p);
	if (control == QStyle::SC_SliderHandle)
	{
		position = value;
		offset = pick(pos - sr.topLeft());
		p->setSliderDown(true);
	}
	if (control != oldControl)
		p->update(sr);
}

void QxtSpanSliderPrivate::drawSpan(QStylePainter* painter, const QRect& rect) const
{
	QStyleOptionSlider opt;
	initStyleOption(&opt);
	const QSlider* p = &qxt_p();
	QRect groove = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, p);
	
	if (opt.orientation == Qt::Horizontal)
		groove.adjust(0, 0, -1, 0);
	else
		groove.adjust(0, 0, 0, -1);
	
	// draw groove
	painter->setPen(QPen(p->palette().color(QPalette::Dark).light(110), 0));

	QColor activeHighlight = p->palette().color(QPalette::Active, QPalette::Highlight);
	QLinearGradient gradient;
	if (opt.orientation == Qt::Horizontal)
	{
		gradient.setStart(groove.center().x(), groove.top());
		gradient.setFinalStop(groove.center().x(), groove.bottom());
	}
	else
	{
		gradient.setStart(groove.left(), groove.center().y());
		gradient.setFinalStop(groove.right(), groove.center().y());
	}
	gradient.setColorAt(0, activeHighlight.dark(120));
	gradient.setColorAt(1, activeHighlight.light(108));
	painter->setBrush(gradient);
	
	if (opt.orientation == Qt::Horizontal)
	{
		painter->setPen(QPen(activeHighlight.dark(130), 0));
		painter->drawRect(rect.intersected(groove));
	}
	else
	{
		painter->setPen(QPen(activeHighlight.dark(150), 0));
		painter->drawRect(rect.intersected(groove));
	}
}

void QxtSpanSliderPrivate::drawHandle(QStylePainter* painter, SpanHandle handle) const
{
	QStyleOptionSlider opt;
	initStyleOption(&opt, handle);
	opt.subControls = QStyle::SC_SliderHandle;
	QStyle::SubControl pressed = (handle == LowerHandle ? lowerPressed : upperPressed);
	if (pressed != QStyle::SC_None)
	{
		opt.activeSubControls = pressed;
		opt.state |= QStyle::State_Sunken;
	}
	painter->drawComplexControl(QStyle::CC_Slider, opt);
}

/*!
    \class QxtSpanSlider QxtSpanSlider
    \ingroup gui
    \brief A slider with two handles.

    QxtSpanSlider is a slider with two handles. QxtSpanSlider is
    handy for letting user to choose an span between min/max.
 */

/*!
    Constructs a new QxtSpanSlider with \a parent.
 */
QxtSpanSlider::QxtSpanSlider(QWidget* parent) : QSlider(parent)
{
	QXT_INIT_PRIVATE(QxtSpanSlider);
}

/*!
    Constructs a new QxtSpanSlider with \a orientation and \a parent.
 */
QxtSpanSlider::QxtSpanSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(orientation, parent)
{
	QXT_INIT_PRIVATE(QxtSpanSlider);
}

/*!
    Destructs the slider.
 */
QxtSpanSlider::~QxtSpanSlider()
{
}

int QxtSpanSlider::lower() const
{
	return qMin(qxt_d().lower, qxt_d().upper);
}

int QxtSpanSlider::upper() const
{
	return qMax(qxt_d().lower, qxt_d().upper);
}

void QxtSpanSlider::setLower(int lower)
{
	setSpan(lower, qxt_d().upper);
}

void QxtSpanSlider::setUpper(int upper)
{
	setSpan(qxt_d().lower, upper);
}

void QxtSpanSlider::setSpan(int lower, int upper)
{
	int l = lower; // qMin(lower, upper);
	int u = upper; // qMax(lower, upper);
	if (l != qxt_d().lower || u != qxt_d().upper)
	{
		if (l != qxt_d().lower)
		{
			qxt_d().lower = l;
			emit lowerChanged(l);
		}
		
		if (u != qxt_d().upper)
		{
			qxt_d().upper = u;
			emit upperChanged(u);
		}
		emit spanChanged(l, u);
		update();
	}
}

void QxtSpanSlider::mousePressEvent(QMouseEvent* event)
{
	if (minimum() == maximum() || (event->buttons() ^ event->button()))
	{
		event->ignore();
		return;
	}
	
	qxt_d().handleMousePress(event->pos(), qxt_d().lowerPressed, qxt_d().lower, QxtSpanSliderPrivate::LowerHandle);
	qxt_d().handleMousePress(event->pos(), qxt_d().upperPressed, qxt_d().upper, QxtSpanSliderPrivate::UpperHandle);
	
	event->accept();
}

void QxtSpanSlider::mouseMoveEvent(QMouseEvent* event)
{
	if (qxt_d().lowerPressed != QStyle::SC_SliderHandle && qxt_d().upperPressed != QStyle::SC_SliderHandle)
	{
		event->ignore();
		return;
	}
	
	QStyleOptionSlider opt;
	qxt_d().initStyleOption(&opt);
	const int m = style()->pixelMetric(QStyle::PM_MaximumDragDistance, &opt, this);
	int newPosition = qxt_d().pixelPosToRangeValue(qxt_d().pick(event->pos()) - qxt_d().offset);
	if (m >= 0)
	{
		const QRect r = rect().adjusted(-m, -m, m, m);
		if (!r.contains(event->pos()))
		{
			newPosition = qxt_d().position;
		}
	}
	
	if (qxt_d().lowerPressed == QStyle::SC_SliderHandle)
	{
		setLower(newPosition);
	}
	else if (qxt_d().upperPressed == QStyle::SC_SliderHandle)
	{
		setUpper(newPosition);
	}
	event->accept();
}

void QxtSpanSlider::mouseReleaseEvent(QMouseEvent* event)
{
	QSlider::mouseReleaseEvent(event);
	qxt_d().lowerPressed = QStyle::SC_None;
	qxt_d().upperPressed = QStyle::SC_None;
}

void QxtSpanSlider::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QStylePainter painter(this);
	
	// ticks
	QStyleOptionSlider opt;
	qxt_d().initStyleOption(&opt);
	opt.subControls = QStyle::SC_SliderTickmarks;
	painter.drawComplexControl(QStyle::CC_Slider, opt);
	
	// groove outside the selection
	opt.sliderPosition = 0;
	opt.subControls = QStyle::SC_SliderGroove;
	painter.drawComplexControl(QStyle::CC_Slider, opt);
	
	// handle rects
	opt.sliderPosition = qxt_d().lower;
	const QRect lr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
	opt.sliderPosition = qxt_d().upper;
	const QRect ur = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
	
	// span
	const int minX = qMin(lr.center().x(), ur.center().x());
	const int maxX = qMax(lr.center().x(), ur.center().x());
	QRect spanRect(QPoint(minX, opt.rect.center().y()-2), QPoint(maxX, opt.rect.center().y()+1));
	qxt_d().drawSpan(&painter, spanRect);
	
	// handles
	qxt_d().drawHandle(&painter, QxtSpanSliderPrivate::LowerHandle);
	qxt_d().drawHandle(&painter, QxtSpanSliderPrivate::UpperHandle);
}
