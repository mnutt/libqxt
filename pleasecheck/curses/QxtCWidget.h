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
#ifndef QXTCWIDGET_H
#define QXTCWIDGET_H

#include <QObject>
#include <QxtCPoint.h>
#include <QxtCRect.h>
#include <QxtPimpl.h>

// DO NOT define this symbol outside of building the library.
#ifndef QXTCURSES_STRUCTS_DEFINED
// This requires a bit of explanation. We do NOT want to include curses.h and
// panel.h in this file because they pollute the global namespace something
// terrible. However, structs and typedefs are incompatible definitions at
// compile time -- though they work fine at link time. So we only define these
// forward declarations for applications, and require curses.h to be included
// before this file for the internal library implementation.
struct PANEL;
struct WINDOW;
#endif

class QxtCKeyEvent;
class QxtCPaintEvent;
class QxtCWidgetPrivate;


/*!
 * \class QxtCWidget
 * \ingroup curses
 * \brief Base class for text-based widgets
 *
 * QxtCWidget is the common base class for all QxtCurses widgets.
 *
 * A widget is the basic component of the user interface. It receives keyboard,
 * mouse, and other events from the user and console window, and it paints
 * itself on the console text display.
 *
 * For more information about widgets in general, consult the QWidget
 * documentation.
 */
class QxtCWidget : public QObject {
Q_OBJECT
public:
    /*!
     * Constructs a new QxtCWidget with the specified parent. If no parent is
     * specified, this widget becomes a top-level window, otherwise this
     * widget becomes a child inside the parent.
     */
    QxtCWidget(QxtCWidget* parent = 0);
    /*!
     * Destroys this QxtCWidget. All of this widget's children are also destroyed.
     */
    virtual ~QxtCWidget();

    /*!
     * Changes the size of the widget to width w and height h.
     */
    void resize(int w, int h);
    /*!
     * Changes the size of the widget to the given size.
     */
    inline void resize(const QxtCSize& sz) { resize(sz.width(), sz.height()); }
    /*!
     * Moves the widget to the specified X and Y coordinates.
     */
    void move(int x, int y);
    /*!
     * Moves the widget to the specified point.
     */
    inline void move(const QxtCPoint& tl) { move(tl.x(), tl.y()); }

    /*!
     * Returns the X coordinate of the widget's left edge.
     */
    int x() const;
    /*!
     * Returns the Y coordinate of the widget's top edge.
     */
    int y() const;
    /*!
     * Returns the width of the widget.
     */
    inline int width() const { return size().width(); }
    /*!
     * Returns the height of the widget.
     */
    inline int height() const { return size().height(); }
    
    /*!
     * Returns the size of the widget.
     */
    QxtCSize size() const;
    /*!
     * Returns the position of the widget's top-left corner.
     */
    inline QxtCPoint pos() const { return QxtCPoint(x(), y()); }
    /*!
     * Returns the widget's bounding rectangle.
     */
    inline QxtCRect rect() const { return QxtCRect(pos(), size()); }

    /*!
     * Returns a pointer to the underlying curses PANEL structure.
     *
     * Only top-level widgets have this window structure. If called on
     * a child widget, winId() returns 0.
     *
     * See also \a handle(), \a isWindow()
     */
    PANEL* winId() const;
    /*!
     * Returns a pointer to the underlying curses WINDOW structure containing this widget.
     *
     * All visible widgets have this window structure. A top-level widget occupies the
     * entire rectangle of the WINDOW structure. Child widgets occupy some smaller
     * rectangle inside it.
     *
     * See also \a winId(), \a isWindow()
     */
    WINDOW* handle() const;
    /*!
     * Asks the widget to repaint itself. The provided rectangle is used to provide
     * a hint about what portions of the widget need to be repainted.
     *
     * See also \a paintEvent()
     */
    void update(const QxtCRect& dirty = QxtCRect());
    /*!
     * Asks the widget to repaint itself. The widget needs h lines to be repainted
     * starting at line y.
     *
     * See also \a paintEvent()
     */
    void update(int y, int h);
    /*!
     * Returns the widget's parent. If the widget is a top-level window, parentWidget() return 0.
     */
    inline QxtCWidget* parentWidget() const { return qobject_cast<QxtCWidget*>(parent()); }
    /*!
     * Returns the top-level window containing this widget.
     */
    QxtCWidget* window() const;
    /*!
     * Returns true if the current widget is at op-level window.
     */
    inline bool isWindow() const { return winId()!=0; }

    /*!
     * Returns the provided point, translated to the coordinate system of the parent widget.
     */
    QxtCPoint mapToParent(const QxtCPoint& point) const;
    /*!
     * Returns the provided point, translated to the coordinate system of the top-level window containing the widget.
     */
    QxtCPoint mapToWindow(const QxtCPoint& point) const;

protected:
    /*!
     * Reimplement this event handler in a subclass in order to handle keystrokes given to this widget.
     *
     * In order for a widget to receive key events, it or one of its children must have the focus.
     * To accept the focus, the widget must call \a setFocusPolicy(). (TODO: Implement focus)
     *
     * The default implementation does nothing.
     */
    virtual void keyEvent(QxtCKeyEvent* event);
    /*!
     * Reimplement this event handler in a subclass in order to paint on this widget.
     *
     * The default implementation erases the contents of the widget.
     */
    virtual void paintEvent(QxtCPaintEvent* event);

private:
    QXT_DECLARE_PRIVATE(QxtCWidget);
};

#endif
