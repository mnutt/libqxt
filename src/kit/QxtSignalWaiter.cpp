/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Adam Higerd 
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include <QxtSignalWaiter.h>
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

QxtSignalWaiter::QxtSignalWaiter(const QObject* sender, const char* signal) : QObject(0) {
    Q_ASSERT(sender && signal);
    connect(sender, signal, this, SLOT(signalCaught()));
}   
    
// Returns true if the signal was caught, returns false if the wait timed out
bool QxtSignalWaiter::wait(const QObject* sender, const char* signal, int msec) {
    QxtSignalWaiter w(sender, signal);
    return w.wait(msec);
}

// Returns true if the signal was caught, returns false if the wait timed out
bool QxtSignalWaiter::wait(int msec) {
    // Check input parameters
    if(msec < -1) return false;

    // activate the timeout
    if(msec != -1) timerID = startTimer(msec);

    // Begin waiting   
    ready = timeout = false;
    while(!ready && !timeout)
        QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);

    // Clean up and return status
    killTimer(timerID);
    return ready || !timeout;
}

void QxtSignalWaiter::signalCaught() {
    ready = true;
}

void QxtSignalWaiter::timerEvent(QTimerEvent* event) {
    killTimer(timerID);
    timeout = true;
}
