#ifndef QXTCKEYEVENT_H
#define QXTCKEYEVENT_H

#include <QEvent>

class QxtCKeyEvent : public QEvent {
public:
    QxtCKeyEvent(int qtKey, Qt::KeyboardModifiers mods = Qt::NoModifier, int rawKey = 0);

    int key();
    Qt::KeyboardModifiers modifiers();
    int nativeScanCode();

private:
    int v, k;
    Qt::KeyboardModifiers m;
};

#endif
