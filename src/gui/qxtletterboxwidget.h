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
#ifndef QXTLETTERBOXWIDGET_H
#define QXTLETTERBOXWIDGET_H

#include <QFrame>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtLetterBoxWidgetPrivate;

class QxtLetterBoxWidget : public QFrame
{
    Q_OBJECT
    QXT_DECLARE_PRIVATE(QxtLetterBoxWidget);
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor RESET clearBackgroundColor)
    Q_PROPERTY(uint widthMultiple READ widthMultiple WRITE setWidthMultiple)
    Q_PROPERTY(uint heightMultiple READ heightMultiple WRITE setHeightMultiple)
    Q_PROPERTY(uint resizeDelay READ resizeDelay WRITE setResizeDelay)

public:
    QxtLetterBoxWidget(QWidget* parent = 0);
    ~QxtLetterBoxWidget();

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& color);
    void clearBackgroundColor();

    QWidget* widget() const;
    void setWidget(QWidget* widget);

    uint widthMultiple() const;
    void setWidthMultiple(uint multiple);

    uint heightMultiple() const;
    void setHeightMultiple(uint multiple);

    uint resizeDelay() const;
    void setResizeDelay(uint delay);

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // QXTLETTERBOXWIDGET_H
