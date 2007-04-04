/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/
#include "private/QxtCurses_p.h"
#include "QxtCFrame.h"

QxtCFrame::QxtCFrame(QxtCWidget* parent) : QxtCWidget(parent) {
}

QxtCFrame::~QxtCFrame() {
}

void QxtCFrame::paintEvent(QxtCPaintEvent* event) {
    QxtCWidget::paintEvent(event);
    if(isWindow()) {
        wborder(handle(), '|', '|', '=', '-', '+', '+', '+', '+');
    } else {
        QxtCPoint pt(mapToWindow(pos()));
        WINDOW* h = handle();
        mvwaddch(h, pt.y(), pt.x(), '+');
        whline(h, '=', width()-2);
        mvwaddch(h, pt.y(), pt.x()+width()-1, '+');
        mvwvline(h, pt.y()+1, pt.x(), '|', height()-2);
        mvwaddch(h, pt.y()+height()-1, pt.x(), '+');
        whline(h, '-', width()-2);
        mvwaddch(h, pt.y()+height()-1, pt.x()+width()-1, '+');
        mvwvline(h, pt.y()+1, pt.x()+width()-1, '|', height()-2);
    }
}
