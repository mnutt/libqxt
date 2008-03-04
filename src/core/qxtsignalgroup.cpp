/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/

#include "qxtsignalgroup.h"
#include <QVector>
#include <QMetaObject>
#include <QtDebug>

class QxtSignalGroupPrivate : public QObject, public QxtPrivate<QxtSignalGroup> {
public:
    QXT_DECLARE_PUBLIC(QxtSignalGroup);
    QxtSignalGroupPrivate() : QObject(0) {
        // since we don't have a metaobject of our own due to not
        // using the Q_OBJECT macro, we need to find methodOffset
        // on our own.
        baseSignal = QObject::staticMetaObject.methodCount();
        emitCount = disconnectCount = 0;
    }

    QVector<bool> emittedSignals;
    int baseSignal, emitCount, disconnectCount;

protected:
    int qt_metacall(QMetaObject::Call _c, int _id, void **_a) {
        Q_UNUSED(_c);
        Q_UNUSED(_a);
        // We don't care about QObject's methods, so skip them
        _id -= baseSignal;
        int ct = emittedSignals.count();    // cached for slight performance gain
        if(_id < 0 || _id > ct) return _id;
        bool& state = emittedSignals[_id];  // more performance caching
        if(!state) {
            if(emitCount == 0)
                qxt_p().firstSignalReceived();
            emitCount++;
            state = true;
            if(emitCount + disconnectCount == ct)
                qxt_p().allSignalsReceived();
        }
        return _id;
    }
};

QxtSignalGroup::QxtSignalGroup(QObject* parent) : QObject(parent) {
    QXT_INIT_PRIVATE(QxtSignalGroup);
}

void QxtSignalGroup::addSignal(QObject* sender, const char* sig) {
    int signalID = sender->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(sig+1));
    if(signalID < 0) {
        qWarning() << "QxtSignalGroup::addSignal: no such signal" << sig;
    } else {
        QMetaObject::connect(sender, signalID, &(qxt_d()), qxt_d().emittedSignals.count() + qxt_d().baseSignal);
        qxt_d().emittedSignals.append(false);
    }
}

void QxtSignalGroup::removeSignal(QObject* sender, const char* sig) {
    if(QObject::disconnect(sender, sig, &(qxt_d()), 0))
        qxt_d().disconnectCount++;
}

void QxtSignalGroup::reset() {
    qxt_d().emittedSignals.fill(false);
    qxt_d().emitCount = 0;
}

void QxtSignalGroup::clear() {
    qxt_d().emittedSignals.clear();
    qxt_d().emitCount = 0;
    qxt_d().disconnectCount = 0;
}
