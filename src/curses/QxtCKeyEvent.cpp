#include "QxtCKeyEvent.h"

QxtCKeyEvent::QxtCKeyEvent(int qtKey, Qt::KeyboardModifiers mods, int rawKey) : QEvent(QEvent::KeyPress) {
    v = qtKey;
    k = rawKey;
    m = mods;
}

int QxtCKeyEvent::key() {
    return v;
}

int QxtCKeyEvent::nativeScanCode() {
    return k;
}

Qt::KeyboardModifiers QxtCKeyEvent::modifiers() {
    return m;
}
