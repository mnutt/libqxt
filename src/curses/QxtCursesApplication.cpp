#include "QxtCursesApplication.h"
#include "private/QxtCursesApplication_p.h"
#include "QxtCKeyEvent.h"
#include <QSocketNotifier>
#include <curses.h>
#include <QDebug>

QxtCursesApplication::QxtCursesApplication(int& argc, char** argv) : QCoreApplication(argc, argv) {
    QXT_INIT_PRIVATE(QxtCursesApplication);
    initscr();
    nonl();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    qxt_d().currentFocus = this;

    QSocketNotifier* keyb = new QSocketNotifier(0, QSocketNotifier::Read, this);
    QObject::connect(keyb, SIGNAL(activated(int)), &qxt_d(), SLOT(handleInput()));
}

QxtCursesApplication::~QxtCursesApplication() {
    endwin();
}

QObject* QxtCursesApplication::focusWidget() {
    return QxtCursesApplication::instance()->qxt_d().currentFocus;
}

void QxtCursesApplicationPrivate::handleInput() {
    int k, v = 0;
    do {
        k = getch();
        if(k==ERR) return;
        Qt::KeyboardModifiers m;
        if(k >= 0x41 && k <= 0x5a) {
            v = k;
            m |= Qt::ShiftModifier;
        } else if(k >= 'a' && k <= 'z') {
            v = k - ('A'-'a');
        } else if(k >= 0x20 && k <= 0x7e) {
            v = k;
        } else if(k >= KEY_F0+1 && k <= KEY_F0+35) {
            v = Qt::Key_F1 + (k - KEY_F0 - 1);
        } else switch(k) {
            case KEY_BREAK:     v = Qt::Key_Pause; break;
            case KEY_DOWN:      v = Qt::Key_Down; break;
            case KEY_UP:        v = Qt::Key_Up; break;
            case KEY_SLEFT:     m |= Qt::ShiftModifier;
            case KEY_LEFT:      v = Qt::Key_Left; break;
            case KEY_SRIGHT:    m |= Qt::ShiftModifier;
            case KEY_RIGHT:     v = Qt::Key_Right; break;
            case KEY_BACKSPACE: v = Qt::Key_Backspace; break;
            case KEY_NPAGE:     v = Qt::Key_PageDown; break;
            case KEY_PPAGE:     v = Qt::Key_PageUp; break;
            case KEY_ENTER:     v = Qt::Key_Enter; break;
            case KEY_SIC:       m |= Qt::ShiftModifier;
            case KEY_IC:
            case KEY_EIC:       v = Qt::Key_Insert; break;
            case KEY_SDC:       m |= Qt::ShiftModifier;
            case KEY_DC:        v = Qt::Key_Delete; break;
            case KEY_SPRINT:    m |= Qt::ShiftModifier;
            case KEY_PRINT:     v = Qt::Key_Print; break;
            case KEY_A1:        m |= Qt::KeypadModifier;
                                v = Qt::Key_Home; break;
            case KEY_A3:        m |= Qt::KeypadModifier;
                                v = Qt::Key_PageUp; break;
            case KEY_B2:        m |= Qt::KeypadModifier;
                                v = Qt::Key_Clear; break;
            case KEY_C1:        m |= Qt::KeypadModifier;
                                v = Qt::Key_End; break;
            case KEY_C3:        m |= Qt::KeypadModifier;
                                v = Qt::Key_PageDown; break;
            case KEY_CLEAR:     v = Qt::Key_Clear; break;
            case KEY_BTAB:      v = Qt::Key_Backtab; break;
            case KEY_CANCEL:    v = Qt::Key_Cancel; break;
            case KEY_SHOME:     m |= Qt::ShiftModifier;
            case KEY_HOME:      v = Qt::Key_Home; break;
            case KEY_SEND:      m |= Qt::ShiftModifier;
            case KEY_END:       v = Qt::Key_End; break;
            case KEY_SSUSPEND:  m |= Qt::ShiftModifier;
            case KEY_SUSPEND:   v = Qt::Key_Sleep; break;
            case KEY_MOUSE:     /* invoke mouse handler */; break;
            case KEY_RESIZE:    /* invoke resize handler */; break;
            default:            v = Qt::Key_unknown; return;
        }
        QCoreApplication::postEvent(currentFocus, new QxtCKeyEvent(v, m, k));
    } while(true);
}
