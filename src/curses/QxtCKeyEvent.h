#ifndef QXTCKEYEVENT_H
#define QXTCKEYEVENT_H

#include <QEvent>

/*!
 * \class QxtCKeyEvent
 * \group curses
 * \brief Describes a keyboard input event
 *
 * The QxtCKeyEvent class describes a keyboard input event.
 */
class QxtCKeyEvent : public QEvent {
public:
    /*!
     * Creates a new QxtCKeyEvent.
     *
     * The qtKey values can be found in the Qt::Key enum. It may be Qt::Key_unknown, meaning
     * that the ncurses key code (passed via rawKey) could not be mapped to a Qt key code.
     */
    QxtCKeyEvent(int qtKey, Qt::KeyboardModifiers mods = Qt::NoModifier, int rawKey = 0)
        : QEvent(QEvent::KeyPress), v(qtKey), k(rawKey), m(mods) {}

    /*!
     * Returns a value from the Qt::Key enum corresponding to the key that triggered the event.
     */
    inline int key() const { return v; }
    /*!
     * Returns the keyboard modifiers pertaining to the keystroke that triggered the event.
     *
     * Note that not all modifiers or combinations of modifiers are available from the
     * curses backend.
     */
    inline Qt::KeyboardModifiers modifiers() const { return m; }
    /*!
     * Returns the native curses key code for the key that triggered the event.
     */
    inline int nativeScanCode() const { return k; }

private:
    int v, k;
    Qt::KeyboardModifiers m;
};

#endif
