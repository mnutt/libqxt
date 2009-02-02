/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtCore module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/

#ifndef QXTRPCSERVICE_P_H
#define QXTRPCSERVICE_P_H

#include "qxtrpcservice.h"
#include <QPointer>
#include <QHash>
#include <QByteArray>
#include <QString>
#include <QPair>

class QxtRPCServiceIntrospector;
class QxtRPCServicePrivate : public QObject, public QxtPrivate<QxtRPCService>
{
    Q_OBJECT
public:
    QxtRPCServicePrivate();
    QXT_DECLARE_PUBLIC(QxtRPCService);

    QxtRPCServiceIntrospector* introspector;
    QxtAbstractConnectionManager* manager;
    QxtAbstractSignalSerializer* serializer;
    QPointer<QIODevice> device;

    QByteArray serverBuffer;
    QHash<quint64, QByteArray> buffers;

    struct SlotDef
    {
        QObject* recv;
        QByteArray slot;
        Qt::ConnectionType type;
        inline bool operator==(const SlotDef& other) const
        {
            return (recv == other.recv) && (slot == other.slot) && (type == other.type);
        }
    };
    QHash<QString, QList<SlotDef> > connectedSlots;
    QHash<QPair<const QMetaObject*, QByteArray>, QList<QByteArray> > slotParameters;

    void dispatchFromServer(const QString& fn, const QVariant& p0 = QVariant(), const QVariant& p1 = QVariant(), const QVariant& p2 = QVariant(),
                            const QVariant& p3 = QVariant(), const QVariant& p4 = QVariant(), const QVariant& p5 = QVariant(),
                            const QVariant& p6 = QVariant(), const QVariant& p7 = QVariant()) const;
    void dispatchFromClient(quint64 id, const QString& fn, const QVariant& p0 = QVariant(), const QVariant& p1 = QVariant(), const QVariant& p2 = QVariant(),
                            const QVariant& p3 = QVariant(), const QVariant& p4 = QVariant(), const QVariant& p5 = QVariant(),
                            const QVariant& p6 = QVariant(), const QVariant& p7 = QVariant()) const;

public Q_SLOTS:
    void clientConnected(QIODevice* dev, quint64 id);
    void clientDisconnected(QIODevice* dev, quint64 id);
    void clientData(quint64 id);

    void serverData();
};

#endif
