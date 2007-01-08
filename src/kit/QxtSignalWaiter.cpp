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
    obj = sender;
    sig = signal;
}   
    
// Returns true if the signal was caught, returns false if the wait timed out
bool QxtSignalWaiter::wait(int msec, const QObject* sender, const char* signal) {
    if(sender!=0 && signal!=0) connect(sender, signal, this, SLOT(signalCaught()));
    else if(obj!=0 && sig!=0) connect(obj, sig, this, SLOT(signalCaught()));
    else if(msec == -1) return false;
    // There would be an else clause here, except you can use this to idle for a specified amount of time
    
    if(msec!=-1) QTimer::singleShot(msec, this, SLOT(timedOut()));
    ready = timeout = false;
    while(!ready && !timeout) QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);
    return ready || !timeout;
}

void QxtSignalWaiter::signalCaught() {
    ready = true;
}

void QxtSignalWaiter::timedOut() {
    timeout = true;
}
