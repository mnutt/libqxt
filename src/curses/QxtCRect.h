#ifndef QXTCRECT_H
#define QXTCRECT_H

#include <QxtCPoint.h>
#include <QxtCSize.h>

class QxtCRect {
public:
    QxtCRect() : _tl(QxtCPoint()), _br(QxtCPoint()) {}
    QxtCRect(int x, int y, int w, int h) : _tl(x,y), _br(x+w,y+h) {}
    QxtCRect(const QxtCPoint& tl, const QxtCPoint& br) : _tl(tl), _br(br) {}
    QxtCRect(const QxtCPoint& tl, const QxtCSize& sz) : _tl(tl), _br(tl.x()+sz.width(), tl.y()+sz.height()) {}
    QxtCRect(const QxtCRect& other) { _tl = other.topLeft(); _br = other.bottomRight(); }

    inline int left() const { return _tl.x(); }
    inline int x() const { return _tl.x(); }
    inline int top() const { return _tl.y(); }
    inline int y() const { return _tl.y(); }
    inline int right() const { return _br.x(); }
    inline int bottom() const { return _br.y(); }

    inline void setLeft(int x) { _tl.setX(x); }
    inline void setX(int x) { _tl.setX(x); }
    inline void setTop(int y) { _tl.setY(y); }
    inline void setY(int y) { _tl.setY(y); }
    inline void setRight(int x) { _br.setX(x); }
    inline void setBottom(int y) { _br.setY(y); }

    inline const QxtCPoint& topLeft() const { return _tl; }
    inline const QxtCPoint& bottomRight() const { return _br; }
    inline QxtCPoint topRight() const { return QxtCPoint(_br.x(), _tl.y()); }
    inline QxtCPoint bottomLeft() const { return QxtCPoint(_tl.x(), _br.y()); }
    inline QxtCSize size() const { return QxtCSize(_br.x()-_tl.x(), _br.y()-_tl.y()); }

    inline void setTopLeft(const QxtCPoint& tl) { _tl = tl; }
    inline void setBottomRight(const QxtCPoint& br) { _br = br; }
    inline void setTopRight(const QxtCPoint& tr) { _br.setX(tr.x()); _tl.setY(tr.y()); }
    inline void setBottomLeft(const QxtCPoint& bl) { _tl.setX(bl.x()); _br.setY(bl.y()); }
    inline void setSize(const QxtCSize& sz) { _br.setX(_tl.x()+sz.width()); _br.setY(_tl.y()+sz.height()); }

    inline int height() const { return _br.y()-_tl.y(); }
    inline int width() const { return _br.x()-_tl.x(); }

    inline void setHeight(int y) { _br.setY(_tl.y() + y); }
    inline void setWidth(int x) { _br.setX(_tl.x() + x); }

    inline const QxtCRect& operator=(const QxtCRect& other) { _tl=other.topLeft(); _br=other.bottomRight(); return *this; }
    inline bool operator==(const QxtCRect& other) const { return _tl==other.topLeft() && _br==other.bottomRight(); }
    
private:
    QxtCPoint _tl, _br;
};

#endif
