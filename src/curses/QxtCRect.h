#ifndef QXTCRECT_H
#define QXTCRECT_H

#include <QtGlobal>
#include <QxtCPoint.h>
#include <QxtCSize.h>

/*!
 * \class QxtCRect
 * \group curses
 * \brief Defines a rectangle
 *
 * The QxtCRect class defines a rectangle.
 *
 * A rectangle is defined by a point and a size, or by two points. Unlike Qt's QRect class,
 * the values returned by \a bottom(), \a right(), and other related functions do not
 * deviate from the true dimensions of the rectangle, because QxtCRect is defined in terms
 * of character cells, not infinitesimal points.
 */
class QxtCRect {
public:
    /*!
     * Constructs a new empty QxtCRect at the origin.
     */
    QxtCRect() : _tl(QxtCPoint()), _br(QxtCPoint()) {}
    /*!
     * Constructs a new QxtCRext with width w and height h starting at (x, y).
     */
    QxtCRect(int x, int y, int w, int h) : _tl(x,y), _br(x+w,y+h) {}
    /*!
     * Constructs a new QxtCRect with corners tl and br.
     */
    QxtCRect(const QxtCPoint& tl, const QxtCPoint& br) : _tl(tl), _br(br) {}
    /*!
     * Constructs a new QxtRect starting at point tl with size sz.
     */
    QxtCRect(const QxtCPoint& tl, const QxtCSize& sz) : _tl(tl), _br(tl.x()+sz.width(), tl.y()+sz.height()) {}

    /*!
     * Returns the X coordinate of the rectangle's left edge. Equivalent to \a x().
     */
    inline int left() const { return _tl.x(); }
    /*!
     * Returns the X coordinate of the rectangle's left edge. Equivalent to \a left().
     */
    inline int x() const { return _tl.x(); }
    /*!
     * Returns the Y coordinate of the rectangle's top edge. Equivalent to \a y().
     */
    inline int top() const { return _tl.y(); }
    /*!
     * Returns the Y coordinate of the rectangle's top edge. Equivalent to \a height().
     */
    inline int y() const { return _tl.y(); }
    /*!
     * Returns the X coordinate of the rectangle's right edge.
     */
    inline int right() const { return _br.x(); }
    /*!
     * Returns the Y coordinate of the rectangle's bottom edge.
     */
    inline int bottom() const { return _br.y(); }

    /*!
     * Sets the X coordinate of the rectangle's left edge. Equivalent to \a setX().
     */
    inline void setLeft(int x) { _tl.setX(x); }
    /*!
     * Sets the X coordinate of the rectangle's left edge. Equivalent to \a setLeft().
     */
    inline void setX(int x) { _tl.setX(x); }
    /*!
     * Sets the Y coordinate of the rectangle's top edge. Equivalent to \a setY().
     */
    inline void setTop(int y) { _tl.setY(y); }
    /*!
     * Sets the Y coordinate of the rectangle's top edge. Equivalent to \a setTop().
     */
    inline void setY(int y) { _tl.setY(y); }
    /*!
     * Sets the X coordinate of the rectangle's right edge.
     */
    inline void setRight(int x) { _br.setX(x); }
    /*!
     * Sets the Y coordinate of the rectangle's bottom edge.
     */
    inline void setBottom(int y) { _br.setY(y); }

    /*!
     * Returns the top-left corner of the rectangle.
     */
    inline const QxtCPoint& topLeft() const { return _tl; }
    /*!
     * Returns the bottom-right corner of the rectangle.
     */
    inline const QxtCPoint& bottomRight() const { return _br; }
    /*!
     * Returns the top-right corner of the rectangle.
     */
    inline QxtCPoint topRight() const { return QxtCPoint(_br.x(), _tl.y()); }
    /*!
     * Returns the bottom-left corner of the rectangle.
     */
    inline QxtCPoint bottomLeft() const { return QxtCPoint(_tl.x(), _br.y()); }
    /*!
     * Returns the size of the rectangle.
     */
    inline QxtCSize size() const { return QxtCSize(_br.x()-_tl.x(), _br.y()-_tl.y()); }

    /*!
     * Sets the top-left corner of the rectangle.
     */
    inline void setTopLeft(const QxtCPoint& tl) { _tl = tl; }
    /*!
     * Sets the bottom-right corner of the rectangle.
     */
    inline void setBottomRight(const QxtCPoint& br) { _br = br; }
    /*!
     * Sets the top-right corner of the rectangle.
     */
    inline void setTopRight(const QxtCPoint& tr) { _br.setX(tr.x()); _tl.setY(tr.y()); }
    /*!
     * Sets the bottom-left corner of the rectangle.
     */
    inline void setBottomLeft(const QxtCPoint& bl) { _tl.setX(bl.x()); _br.setY(bl.y()); }
    /*!
     * Sets the size of the rectangle.
     */
    inline void setSize(const QxtCSize& sz) { _br.setX(_tl.x()+sz.width()); _br.setY(_tl.y()+sz.height()); }

    /*!
     * Returns the height of the rectangle.
     */
    inline int height() const { return _br.y()-_tl.y(); }
    /*!
     * Returns the width of the rectangle.
     */
    inline int width() const { return _br.x()-_tl.x(); }

    /*!
     * Sets the height of the rectangle.
     */
    inline void setHeight(int y) { _br.setY(_tl.y() + y); }
    /*!
     * Sets the width of the rectangle.
     */
    inline void setWidth(int x) { _br.setX(_tl.x() + x); }

    /*!
     * Sets the size and position of the rectangle to the size and position of another rectangle.
     */
    inline const QxtCRect& operator=(const QxtCRect& other) { _tl=other.topLeft(); _br=other.bottomRight(); return *this; }
    /*!
     * Compares two rectangles for equality.
     *
     * Two rectangles are equal if and only if they have the same sizes and same top-left corner.
     */
    inline bool operator==(const QxtCRect& other) const { return _tl==other.topLeft() && _br==other.bottomRight(); }
    /*!
     * Compares two rectangles for inequality.
     *
     * Two rectangles are equal if and only if they have the same sizes and same top-left corner.
     */
    inline bool operator!=(const QxtCRect& other) const { return _tl!=other.topLeft() || _br!=other.bottomRight(); }
    
private:
    QxtCPoint _tl, _br;
};
Q_DECLARE_TYPEINFO(QxtCRect, Q_MOVABLE_TYPE);

#endif
