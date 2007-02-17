#include "QxtCurses_p.h"
#include "QxtCWidget.h"
#include "QxtCKeyEvent.h"
#include "QxtCPaintEvent.h"
#include <QDebug>

QxtCWidget::QxtCWidget(QxtCWidget* parent) : QObject(parent), maxX(1), maxY(1), xpos(0), ypos(0) {
    if(!parent) {
        WINDOW* p = newwin(1,1,0,0);
        win = new_panel(p);
        offX = offY = 0;
    } else {
        win = 0;
        QxtCWidget* p = parentWidget();
        QxtCPoint pt;
        while(p) {
            pt = p->mapToParent(pt);
            p = p->parentWidget();
        }
        offX = pt.x();
        offY = pt.y();
    }
} 

QxtCWidget::~QxtCWidget() {
    if(win) {
        delwin(handle());
        del_panel(win);
    }
}

QxtCWidget* QxtCWidget::window() const {
    QxtCWidget* w = const_cast<QxtCWidget*>(this);
    while(!w->isWindow()) w = w->parentWidget();
    return w;
}

WINDOW* QxtCWidget::handle() const {
    if(win)
        return panel_window(win);
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
    if(win) {
        wresize(handle(), h, w);
        replace_panel(win, handle());
    }
    int oldMaxY = maxY;
    maxX = w;
    maxY = h;
    int t = oldMaxY - maxY;
    if(t > 0) 
        window()->update(offY, oldMaxY + t);
    else
        window()->update(offY, maxY - t);
}

void QxtCWidget::move(int x, int y) {
    xpos = x; 
    ypos = y;
    int oldOffY = offY;
    if(win) {
        move_panel(win, y, x);
    } else {
        QxtCWidget* w = parentWidget();
        if(w) {
            QxtCPoint p = parentWidget()->mapToParent(QxtCPoint(x, y));
            offX = p.x();
            offY = p.y();
        } else {
            offX = x;
            offY = y;
        }
    }
    QxtCWidget* w;
    foreach(QObject* c, children()) {
        w = qobject_cast<QxtCWidget*>(c);
        if(!w) continue;
        w->move(w->x(), w->y());
    }
    int t = oldOffY - offY;
    if(t > 0) 
        window()->update(offY, height() + t);
    else
        window()->update(oldOffY, height() - t);
}

QxtCSize QxtCWidget::size() const {
    if(win) {
        int w, h;
        getmaxyx(handle(), h, w);
        return QxtCSize(w, h);
    } else {
        return QxtCSize(maxX, maxY);
    }
}

void QxtCWidget::update(const QxtCRect& dirty) {
    if(dirty.height()==0) {
        window()->update(offY, maxY);
    } else {
        window()->update(offY+dirty.top(), dirty.height());
    }
}

void QxtCWidget::update(int y, int h) {
    if(win) {
        wredrawln(handle(), y, h);
        QxtCPaintEvent e(y,h);
        paintEvent(&e);
        update_panels();
        refresh();
    } else {
        window()->update(offY+y, h);
    }
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
