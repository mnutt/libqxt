/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtGui module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/
#include "qxtletterboxwidget.h"
#include "qxtletterboxwidget_p.h"

QxtLetterBoxWidgetPrivate::QxtLetterBoxWidgetPrivate() : center(0), multX(1), multY(1)
{
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SLOT(resize()));
}

void QxtLetterBoxWidgetPrivate::resize()
{
    if (!center)
        return;

    const int width = qxt_p().width();
    const int height = qxt_p().height();

    if (width < center->minimumWidth() || height < center->minimumHeight())
    {
        center->resize(center->minimumSize());
        center->move((width - center->width()) / 2, (height - center->height()) / 2);
        return;
    }

    int hmargin = (width - center->minimumWidth()) % multX;
    int vmargin = (height - center->minimumHeight()) % multY;
    int w = width - hmargin, h;

    if (center->heightForWidth(w) == -1)
    {
        h = height - vmargin;
    }
    else
    {
        h = center->heightForWidth(w);
        if (h > height && center->heightForWidth(w / 2) < w)
        {   // directly proportional
            // First, make an educated guess that such an object maintains a predictable aspect ratio
            uint maxw = w, minw = w / 2;
            if (center->minimumWidth() != 0)
                w = uint(float(center->minimumWidth()) / center->minimumHeight() * height);
            else
                w = uint(float(w) / h * height);
            w -= (w - center->minimumWidth()) % multX;
            h = center->heightForWidth(w);
            while (uint(height - h) > multY || height < h)
            {
                // Educated guess has failed! Binary search time.
                w = (maxw + minw) / 2;
                h = center->heightForWidth(w);
                if (h > height)
                    maxw = w;
                else
                    minw = w;
                if (minw >= maxw)
                    break;
            }
        } // inverse proportion implies no amount of narrowing will make it fit vertically
    }
    center->move((width - w) / 2, (height - h) / 2);
    center->resize(w, h);
}

/*!
    \class QxtLetterBoxWidget QxtLetterBoxWidget
    \ingroup QxtGui
    \brief A letter box widget.

    QxtLetterBoxWidget preserves the aspect ratio of its central widget.
 */

/*!
    Constructs a new QxtLetterBoxWidget with \a parent.
 */
QxtLetterBoxWidget::QxtLetterBoxWidget(QWidget* parent) : QFrame(parent)
{
    QXT_INIT_PRIVATE(QxtLetterBoxWidget);
}

/*!
    Destructs the group box.
 */
QxtLetterBoxWidget::~QxtLetterBoxWidget()
{
}

/*!
    \property QxtLetterBoxWidget::backgroundColor
    \brief This property holds the background color

    \note This property corresponds to \b QPalette::Window. Setting
    this property also sets property QWidget::autoFillBackground
    property as \b true.
 */
QColor QxtLetterBoxWidget::backgroundColor() const
{
    return palette().color(QPalette::Window);
}

void QxtLetterBoxWidget::setBackgroundColor(const QColor& color)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
    setAutoFillBackground(true);
}

/*!
    Returns the central widget for the letter box.
    This function returns zero if the central widget has not been set.

    \sa setCentralWidget()
 */
QWidget* QxtLetterBoxWidget::centralWidget() const
{
    return qxt_d().center;
}

/*!
    Sets the given widget to be the letter box's central widget.

    \note QxtLetterBox takes ownership of the widget pointer
    and deletes it at the appropriate time.

    \sa centralWidget()
 */
void QxtLetterBoxWidget::setCentralWidget(QWidget* widget)
{
    if (qxt_d().center && qxt_d().center != widget)
        qxt_d().center->deleteLater();
    qxt_d().center = widget;
    if (widget)
        widget->setParent(this);
    qxt_d().resize();
}

/*!
    \property QxtLetterBoxWidget::widthMultiple
    \brief This property holds the width multiple

    The default value is \b 1
 */
uint QxtLetterBoxWidget::widthMultiple() const
{
    return qxt_d().multX;
}

void QxtLetterBoxWidget::setWidthMultiple(uint multiple)
{
    if (qxt_d().multX != multiple)
    {
        qxt_d().multX = multiple;
        qxt_d().resize();
    }
}

/*!
    \property QxtLetterBoxWidget::heightMultiple
    \brief This property holds the height multiple

    The default value is \b 1
 */
uint QxtLetterBoxWidget::heightMultiple() const
{
    return qxt_d().multY;
}

void QxtLetterBoxWidget::setHeightMultiple(uint multiple)
{
    if (qxt_d().multY != multiple)
    {
        qxt_d().multY = multiple;
        qxt_d().resize();
    }
}

uint QxtLetterBoxWidget::resizeDelay() const
{
    return qxt_d().timer.interval();
}

void QxtLetterBoxWidget::setResizeDelay(uint delay)
{
    qxt_d().timer.setInterval(delay);
}

/*!
    \reimp
 */
void QxtLetterBoxWidget::resizeEvent(QResizeEvent* event)
{
    QFrame::resizeEvent(event);
    qxt_d().timer.start();
}
