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
#include "QxtCWidget.h"
#include "QxtCKeyEvent.h"
#include "QxtCPaintEvent.h"
#include <QDebug>

class QxtCWidgetPrivate : public QxtPrivate<QxtCWidget> {
public:
    QXT_DECLARE_PUBLIC(QxtCWidget);
    QxtCWidgetPrivate() : win(0), offX(0), offY(0), maxX(1), maxY(1), xpos(0), ypos(0) {}

    PANEL* win;
    int offX, offY, maxX, maxY, xpos, ypos;
};

QxtCWidget::QxtCWidget(QxtCWidget* parent) : QObject(parent) {
    QXT_INIT_PRIVATE(QxtCWidget);
    QxtCWidgetPrivate& d = qxt_d();
    if(!parent) {
        WINDOW* p = newwin(1,1,0,0);
        d.win = new_panel(p);
        d.offX = d.offY = 0;
    } else {
        d.win = 0;
        QxtCWidget* p = parentWidget();
        QxtCPoint pt;
        while(p) {
            pt = p->mapToParent(pt);
            p = p->parentWidget();
        }
        d.offX = pt.x();
        d.offY = pt.y();
    }
} 

QxtCWidget::~QxtCWidget() {
    if(isWindow()) {
        delwin(handle());
        del_panel(qxt_d().win);
    }
}

int QxtCWidget::x() const {
    return qxt_d().xpos;
}

int QxtCWidget::y() const {
    return qxt_d().ypos;
}

PANEL* QxtCWidget::winId() const {
    return qxt_d().win;
} 

QxtCWidget* QxtCWidget::window() const {
    QxtCWidget* w = const_cast<QxtCWidget*>(this);
    while(!w->isWindow()) w = w->parentWidget();
    return w;
}

WINDOW* QxtCWidget::handle() const {
    if(isWindow())
        return panel_window(qxt_d().win);
    return window()->handle();
}

void QxtCWidget::keyEvent(QxtCKeyEvent* event) { Q_UNUSED(event); }

void QxtCWidget::paintEvent(QxtCPaintEvent* event) {
    QxtCWidget* w;
    int t;
    if(event->height == 0) event->height = height();
    if(isWindow()) {
        int end = event->start + event->height;
        for(int i=event->start; i<end; i++) {
            mvwhline(handle(), i, 0, ' ', width());
        }
    }
    foreach(QObject* c, children()) {
        w = qobject_cast<QxtCWidget*>(c);
        if(!w) continue;
        t = w->y() - event->start;
        if(-t > w->height() || t > event->height) continue;
        QxtCPaintEvent e(-t, -t+event->height);
        w->paintEvent(&e);
    }
}

void QxtCWidget::resize(int w, int h) {
    if(isWindow()) {
        wresize(handle(), h, w);
        replace_panel(qxt_d().win, handle());
    }
    QxtCWidgetPrivate& d = qxt_d();
    int oldMaxY = d.maxY;
    d.maxX = w;
    d.maxY = h;
    int t = oldMaxY - h;
    if(t > 0) 
        window()->update(d.offY, oldMaxY + t);
    else
        window()->update(d.offY, h - t);
}

void QxtCWidget::move(int x, int y) {
    QxtCWidgetPrivate& d = qxt_d();
    d.xpos = x; 
    d.ypos = y;
    int oldOffY = d.offY;
    if(isWindow()) {
        move_panel(d.win, y, x);
    } else {
        QxtCWidget* w = parentWidget();
        if(w) {
            QxtCPoint p = parentWidget()->mapToParent(QxtCPoint(x, y));
            d.offX = p.x();
            d.offY = p.y();
        } else {
            d.offX = x;
            d.offY = y;
        }
    }
    QxtCWidget* w;
    foreach(QObject* c, children()) {
        w = qobject_cast<QxtCWidget*>(c);
        if(!w) continue;
        w->move(w->x(), w->y());
    }
    int t = oldOffY - d.offY;
    if(t > 0) 
        window()->update(d.offY, height() + t);
    else
        window()->update(oldOffY, height() - t);
}

QxtCSize QxtCWidget::size() const {
    return QxtCSize(qxt_d().maxX, qxt_d().maxY);
}

void QxtCWidget::update(const QxtCRect& dirty) {
    if(dirty.height()==0) {
        window()->update(qxt_d().offY, qxt_d().maxY);
    } else {
        window()->update(qxt_d().offY+dirty.top(), dirty.height());
    }
}

void QxtCWidget::update(int y, int h) {
    if(isWindow()) {
        wredrawln(handle(), y, h);
        QxtCPaintEvent e(y,h);
        paintEvent(&e);
        update_panels();
        refresh();
    } else {
        window()->update(qxt_d().offY+y, h);
    }
}

QxtCPoint QxtCWidget::mapToParent(const QxtCPoint& point) const {
    return QxtCPoint(point.x() + qxt_d().offX, point.y() + qxt_d().offY);
}

QxtCPoint QxtCWidget::mapToWindow(const QxtCPoint& point) const {
    QxtCWidget* p = parentWidget();
    QxtCPoint pt(point);
    while(p) {
        pt = p->mapToParent(pt);
        p = p->parentWidget();
    }
    return pt;
}
