#ifndef QXTCWIDGET_H
#define QXTCWIDGET_H

#include <QObject>
#include <QxtCPoint.h>
#include <QxtCRect.h>

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
class QxtCWidget : public QObject {
Q_OBJECT
public:
    QxtCWidget(QxtCWidget* parent = 0);
    virtual ~QxtCWidget();

    void resize(int w, int h);
    inline void resize(const QxtCSize& sz) { resize(sz.width(), sz.height()); }
    void move(int x, int y);
    inline void move(const QxtCPoint& tl) { move(tl.x(), tl.y()); }

    inline int x() const { return xpos; }
    inline int y() const { return ypos; }
    inline int width() const { return size().width(); }
    inline int height() const { return size().height(); }
    
    QxtCSize size() const;
    inline QxtCPoint pos() const { return QxtCPoint(xpos, ypos); }
    inline QxtCRect rect() const { return QxtCRect(pos(), size()); }

    inline PANEL* winId() const { return win; }
    WINDOW* handle() const;
    void update(const QxtCRect& dirty = QxtCRect());
    void update(int y, int h);
    inline QxtCWidget* parentWidget() const { return qobject_cast<QxtCWidget*>(parent()); }
    QxtCWidget* window() const;
    inline bool isWindow() const { return win; }

    inline QxtCPoint mapToParent(const QxtCPoint& point) const { return QxtCPoint(point.x() + offX, point.y() + offY); }
    QxtCPoint mapToWindow(const QxtCPoint& point) const;

protected:
    virtual void keyEvent(QxtCKeyEvent* event);
    virtual void paintEvent(QxtCPaintEvent* event);

private:
    PANEL* win;
    int offX, offY, maxX, maxY, xpos, ypos;
};

#endif
