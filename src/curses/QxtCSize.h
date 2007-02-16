#ifndef QXTCSIZE_H
#define QXTCSIZE_H

#include <QxtCSize.h>

class QxtCSize {
public:
    QxtCSize() : _br(QxtCPoint()) {}
    QxtCSize(int w, int h) : _br(QxtCPoint(w, h)) {}
    QxtCSize(const QxtCSize& other) { setHeight(other.height()); setWidth(other.width());}

    inline int height() const { return _br.y(); }
    inline int width() const { return _br.x(); }

    inline void setHeight(int h) { _br.setY(h); }
    inline void setWidth(int w) { _br.setX(w); }

    inline const QxtCSize& operator=(const QxtCSize& other) { _br.setX(other.width()); _br.setY(other.height()); return *this; }
    inline bool operator==(const QxtCSize& other) const { return _br.x()==other.width() && _br.y()==other.height(); }

private:
    QxtCPoint _br;
};

#endif
