#ifndef QXTCSIZE_H
#define QXTCSIZE_H

#include <QtGlobal>

/*!
 * \class QxtCSize
 * \ingroup curses
 * \brief Defines the size of a two-dimensional object
 *
 * The QxtCSize class defines the size of a two-dimensional object.
 *
 * A size is defined by its width and height.
 */
class QxtCSize {
public:
    /*!
     * Constructs a new empty QxtCSize, that is, with zero height and width.
     */
    QxtCSize() : _w(0), _h(0) {}
    /*!
     * Constructs a new QxtCSize with width w and height h.
     */
    QxtCSize(int w, int h) : _w(w), _h(h) {}

    /*!
     * Returns the height.
     */
    inline int height() const { return _h; }
    /*!
     * Returns the width.
     */
    inline int width() const { return _w; }

    /*!
     * Sets the height.
     */
    inline void setHeight(int h) { _h = h; }
    /*!
     * Sets the width.
     */
    inline void setWidth(int w) { _w = w; }

    /*!
     * Sets the size to the width and height of another size.
     */
    inline const QxtCSize& operator=(const QxtCSize& other) { _w = other.width(); _h = other.height(); return *this; }
    /*!
     * Compares two sizes for equality.
     *
     * Two sizes are equal if and only if both widths and both heights are equal.
     */
    inline bool operator==(const QxtCSize& other) const { return _w==other.width() && _h==other.height(); }
    /*!
     * Compares two sizes for inequality.
     *
     * Two sizes are equal if and only if both widths and both heights are equal.
     */
    inline bool operator!=(const QxtCSize& other) const { return _w!=other.width() || _h!=other.height(); }

private:
    int _w, _h;
};
Q_DECLARE_TYPEINFO(QxtCSize, Q_PRIMITIVE_TYPE);

#endif
