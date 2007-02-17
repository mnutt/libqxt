#ifndef QXTCPOINT_H
#define QXTCPOINT_H

#include <QtGlobal>

/*!
 * \class QxtCPoint
 * \ingroup curses
 * \brief Defines the location of a character cell
 *
 * The QxtCPoint class defines the location of a character cell.
 *
 * A cell is defined by its X and Y coordinates.
 */
class QxtCPoint {
public:
    /*!
     * Constructs a new QxtCPoint at the top-left corner, that is, with coordinates (0, 0).
     */
    QxtCPoint() : _x(0), _y(0) {}
    /*!
     * Constructs a new QxtCPoint with coordinates (x, y).
     */
    QxtCPoint(int x, int y) : _x(x), _y(y) {}

    /*!
     * Returns a reference to the X coordinate that can be modified.
     */
    inline int& rx() { return _x; }
    /*!
     * Returns a reference to the Y coordinate that can be modified.
     */
    inline int& ry() { return _y; }
    /*!
     * Returns the X coordinate of the point.
     */
    inline int x() const { return _x; }
    /*!
     * Returns the Y coordinate of the point.
     */
    inline int y() const { return _y; }
    /*!
     * Sets the X coordinate of the point.
     */
    inline void setX(int x) { _x = x; }
    /*!
     * Sets the Y coordinate of the point.
     */
    inline void setY(int y) { _y = y; }

    /*!
     * Sets the coordinates of the point to the coordinates of another point.
     */
    inline const QxtCPoint& operator=(const QxtCPoint& other) { _x = other.x(); _y = other.y(); return *this; }
    /*!
     * Compares two points for equality.
     *
     * Two points are equal if and only if both X coordinates and both Y coordinates are equal.
     */
    inline bool operator==(const QxtCPoint& other) const { return _x==other.x() && _y==other.y(); }
    /*!
     * Compares two points for inequality.
     *
     * Two points are equal if and only if both X coordinates and both Y coordinates are equal.
     */
    inline bool operator!=(const QxtCPoint& other) const { return _x!=other.x() || _y!=other.y(); }

private:
    int _x, _y;
};
Q_DECLARE_TYPEINFO(QxtCPoint, Q_PRIMITIVE_TYPE);

#endif
