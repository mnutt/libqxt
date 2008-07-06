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
#include <QLayout>
#include <QStyle>

QxtLetterBoxWidgetPrivate::QxtLetterBoxWidgetPrivate() : center(0), multX(1), multY(1)
{
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SLOT(resize()));
}

void QxtLetterBoxWidgetPrivate::resize()
{
    if (center)
    {
        QSize size(multX, multY);
        size.scale(qxt_p().size(), Qt::KeepAspectRatio);
        size = QLayout::closestAcceptableSize(center, size);
        QRect rect = QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size, qxt_p().rect());
        center->setGeometry(rect);
    }
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
    and unsetting the property also sets the property 
    \b QWidget::autoFillBackground as \b true or \b false, respectively.
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

void QxtLetterBoxWidget::unsetBackgroundColor()
{
    setBackgroundColor(QColor());
    setAutoFillBackground(false);
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
    {
        widget->setParent(this);
        qxt_d().resize();
    }
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

/*!
    \property QxtLetterBoxWidget::resizeDelay
    \brief This property holds the delay of resize

    The default value is \b 0 which means immediate resize.

    Using a short resize delay might be useful if the central
    widget is complex and resizing it is expensive.
 */
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
    if (resizeDelay() > 0)
        qxt_d().timer.start();
    else
        qxt_d().resize();
}
