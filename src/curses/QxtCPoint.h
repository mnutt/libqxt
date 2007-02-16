#ifndef QXTCPOINT_H
#define QXTCPOINT_H

class QxtCPoint {
public:
    QxtCPoint() : _x(0), _y(0) {}
    QxtCPoint(int x, int y) : _x(x), _y(y) {}
    QxtCPoint(const QxtCPoint& other) { _x = other.x(); _y = other.y(); }

    inline int& rx() { return _x; }
    inline int& ry() { return _y; }
    inline int x() const { return _x; }
    inline int y() const { return _y; }
    inline void setX(int x) { _x = x; }
    inline void setY(int y) { _y = y; }

    inline const QxtCPoint& operator=(const QxtCPoint& other) { _x = other.x(); _y = other.y(); return *this; }
    inline bool operator==(const QxtCPoint& other) const { return _x==other.x() && _y==other.y(); }

private:
    int _x, _y;
};

#endif
