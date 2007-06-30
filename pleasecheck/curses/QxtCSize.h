/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/
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
