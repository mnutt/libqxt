#include "QxtCPaintEvent.h"

QxtCPaintEvent::QxtCPaintEvent() : QEvent(QEvent::Paint), start(0), height(0) {}

QxtCPaintEvent::QxtCPaintEvent(int y, int h) : QEvent(QEvent::Paint), start(y), height(h) {}

QxtCPaintEvent::QxtCPaintEvent(const QxtCRect& dirty) : QEvent(QEvent::Paint), start(dirty.top()), height(dirty.height()) {}
