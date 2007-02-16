#ifndef QXTCPAINTEVENT_H
#define QXTCPAINTEVENT_H

#include <QEvent>
#include <QxtCRect.h>

class QxtCPaintEvent : public QEvent {
public:
    QxtCPaintEvent();
    QxtCPaintEvent(int y, int h);
    QxtCPaintEvent(const QxtCRect& dirty);
    int start, height;
};

#endif
