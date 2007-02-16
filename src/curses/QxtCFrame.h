#ifndef QXTCFRAME_H
#define QXTCFRAME_H

#include "QxtCWidget.h"

class QxtCFrame : public QxtCWidget {
Q_OBJECT
public:
    QxtCFrame(QxtCWidget* parent = 0);
    virtual ~QxtCFrame();

public:
    virtual void paintEvent(QxtCPaintEvent* event);
};

#endif
