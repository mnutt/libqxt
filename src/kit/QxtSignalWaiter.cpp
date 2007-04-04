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
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/

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
    if(msec != -1) killTimer(timerID);
    return ready || !timeout;
}

void QxtSignalWaiter::signalCaught() {
    ready = true;
}

void QxtSignalWaiter::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event);
    killTimer(timerID);
    timeout = true;
}
