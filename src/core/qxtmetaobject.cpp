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
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/
#include "qxtmetaobject.h"

#include <QByteArray>
#include <QMetaObject>
#include <QMetaMethod>
#include <QtDebug>

class QxtBoundArgument {
    // This class intentionally left blank
};
Q_DECLARE_METATYPE(QxtBoundArgument)
    
class QxtBoundFunction : public QObject {
public:
    QByteArray sig, bindTypes[10];
    QGenericArgument arg[10], p[10];
    void* data[10];

    QxtBoundFunction(QObject* receiver, const char* invokable, QGenericArgument* params[10], QByteArray types[10]) : QObject(receiver), sig(invokable) {
        for(int i=0; i<10; i++) {
            if(!params[i]) break;
            if(QByteArray(params[i]->name()) == "QxtBoundArgument") {
                arg[i] = QGenericArgument("QxtBoundArgument", params[i]->data());
            } else {
                data[i] = QMetaType::construct(QMetaType::type(params[i]->name()), params[i]->data());
                arg[i] = p[i] = QGenericArgument(params[i]->name(), data[i]);
            }
            bindTypes[i] = types[i];
        }
    }
    
    ~QxtBoundFunction() {
        for(int i=0; i<10; i++) {
            if(arg[i].name() == 0) return;
            if(QByteArray(arg[i].name()) != "QxtBoundArgument") QMetaType::destroy(QMetaType::type(arg[i].name()), arg[i].data());
        }
    }

    int qt_metacall(QMetaObject::Call _c, int _id, void **_a) {
        _id = QObject::qt_metacall(_c, _id, _a);
        if(_id < 0)
            return _id;
        if(_c == QMetaObject::InvokeMetaMethod) {
            if(_id == 0) {
                for(int i = 0; i < 10; i++) {
                    if(QByteArray(arg[i].name()) == "QxtBoundArgument") {
                        p[i] = QGenericArgument(bindTypes[i].constData(), _a[(int)(arg[i].data())]);
                    }
                }
                if(!QMetaObject::invokeMethod(parent(), QxtMetaObject::methodName(sig.constData()), p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9])) {
                    qWarning() << "QxtBoundFunction: call to " << sig << " failed";
                }
            }
            _id = -1;
        }
        return _id;
    }
};

namespace QxtMetaObject
{

/*!
    \fn QxtMetaObject::methodName()

    Returns the name of the given method.

    Example usage:
    \code
    QByteArray method = QxtMetaObject::methodName(" int foo ( int bar, double baz )");
    // method is now "foo"
    \endcode
 */
QByteArray methodName(const char* method)
{
    QByteArray name = QMetaObject::normalizedSignature(method);
    if (name.startsWith("1") || name.startsWith("2"))
        name = name.mid(1);
    const int idx = name.indexOf("(");
    if (idx != -1)
        name.truncate(idx);
    return name;
}

QxtBoundFunction* bind(QObject* recv, const char* invokable, QGenericArgument p1, QGenericArgument p2,
        QGenericArgument p3, QGenericArgument p4, QGenericArgument p5, QGenericArgument p6,
        QGenericArgument p7, QGenericArgument p8, QGenericArgument p9, QGenericArgument p10) {
    if(!recv) {
        qWarning() << "QxtMetaObject::bind: cannot connect to null QObject";
        return 0;
    }

    QGenericArgument* args[10] = { &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10 };
    QByteArray connSlot("2"), recvSlot(QMetaObject::normalizedSignature(invokable)), bindTypes[10];
    const QMetaObject* meta = recv->metaObject();
    int methodID = meta->indexOfMethod(recvSlot.mid(1).constData());
    if(methodID == -1) {
        qWarning() << "QxtMetaObject::bind: no such method " << recvSlot;
        return 0;
    }
    QMetaMethod method = meta->method(methodID);
    int argCount = method.parameterTypes().count();

    connSlot += QxtMetaObject::methodName(invokable) + "(";
    for(int i=0; i<10; i++) {
        if(args[i]->name() == 0) break;         // done
        if(i >= argCount) {
            qWarning() << "QxtMetaObject::bind: too many arguments passed to " << invokable;
            return 0;
        }
        if(i > 0) connSlot += ",";              // argument separator
        if(QByteArray(args[i]->name()) == "QxtBoundArgument") {
            Q_ASSERT_X((int)(args[i]->data()) > 0 && (int)(args[i]->data()) <= 10, "QXT_BIND", "invalid argument number");
            connSlot += method.parameterTypes()[i];
            bindTypes[i] = method.parameterTypes()[i];
        } else {
            connSlot += args[i]->name();        // type name
        }
    }
    connSlot = QMetaObject::normalizedSignature(connSlot += ")");

    if(!QMetaObject::checkConnectArgs(recvSlot.constData(), connSlot.constData())) {
        qWarning() << "WxtMetaObject::bind: provided parameters " << connSlot.mid(connSlot.indexOf('(')) << " is incompatible with " << invokable;
        return 0;
    }

    return new QxtBoundFunction(recv, invokable, args, bindTypes);
}

bool connect(QObject* sender, const char* signal, QxtBoundFunction* slot, Qt::ConnectionType type) {
    const QMetaObject* meta = sender->metaObject();
    int methodID = meta->indexOfMethod(meta->normalizedSignature(signal).mid(1).constData());
    if(methodID < 0) {
        qWarning() << "QxtMetaObject::connect: no such signal: " << QByteArray(signal).mid(1);
        return false;
    }

    return QMetaObject::connect(sender, methodID, slot, QObject::staticMetaObject.methodCount(), (int)(type));
}
}
