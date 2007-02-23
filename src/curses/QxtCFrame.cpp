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
