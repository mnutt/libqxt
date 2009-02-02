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

#include "qxtrpcservice.h"
#include "qxtrpcservice_p.h"
#include "qxtabstractconnectionmanager.h"
#include "qxtdatastreamsignalserializer.h"
#include "qxtmetaobject.h"
#include "qxtboundfunction.h"
#include <QIODevice>
#include <QtDebug>
#include <QMetaObject>
#include <QMetaType>
#include <QMetaMethod>
#include <QMultiHash>
#include <QList>
#include <QString>
#include <QByteArray>
#include <QPair>

class QxtRPCServiceIntrospector : public QObject
{
public:
    QxtRPCService* rpc;
    quint32 nextSlotID;

    QHash<QPair<const QMetaObject*, QByteArray>, int> signalIDs, methodIDs;
    QList<QList<int> > signalParameters;
    typedef QPair<QObject*, QByteArray> SignalDef;
    QMultiHash<SignalDef, int> signalToId;
    QHash<int, int> idToParams;
    QMultiHash<int, QString> idToRpc;

    QxtRPCServiceIntrospector(QxtRPCService* parent) : QObject(parent), rpc(parent)
    {
        nextSlotID = QObject::staticMetaObject.methodCount();
    }

    bool addSignal(QObject* obj, const char* signature, const QString& rpcFunction)
    {
        const QMetaObject* meta = obj->metaObject();
        QByteArray norm = QxtMetaObject::methodSignature(signature);
        QPair<const QMetaObject*, QByteArray> signal = qMakePair(meta, norm);
        int sigID, methodID;
        if (signalIDs.count(signal))
        {
            // already cached
            sigID = signalIDs.value(signal);
            methodID = methodIDs.value(signal);
        }
        else
        {
            methodID = meta->indexOfMethod(norm.constData());
            if (methodID < 0)
            {
                qWarning() << "QxtRPCService::attachSignal: " << obj << "::" << signature << " does not exist";
                return false;
            }
            QList<QByteArray> types = meta->method(methodID).parameterTypes();
            QList<int> typeIDs;
            int ct = types.count();
            for (int i = 0; i < ct; i++)
            {
                int typeID = QMetaType::type(types.value(i).constData());
                if (typeID <= 0)
                {
                    qWarning() << "QxtRPCService::attachSignal: cannot queue arguments of type " << types.value(i);
                    return false;
                }
                typeIDs.append(typeID);
            }
            int nextSignalID = signalParameters.count();
            signalIDs[signal] = nextSignalID;
            methodIDs[signal] = methodID;
            signalParameters.append(typeIDs);
            sigID = nextSignalID;
        }
        signalToId.insert(qMakePair(obj, norm), nextSlotID);
        idToRpc.insert(nextSlotID, rpcFunction.isEmpty() ? norm : rpcFunction);
        idToParams[nextSlotID] = sigID;
        QMetaObject::connect(obj, methodID, this, nextSlotID);
        do
        {
            nextSlotID++;
        }
        while (nextSlotID < quint32(QObject::staticMetaObject.methodCount()) || idToParams.contains(nextSlotID));
        return true;
    }

    void disconnectObject(QObject* obj)
    {
        const QMetaObject* meta = obj->metaObject();
        foreach(const SignalDef& sig, signalToId.keys())
        {
            if (sig.first != obj) continue;
            int methodID = methodIDs[qMakePair(meta, sig.second)];
            foreach(int id, signalToId.values(sig))
            {
                QMetaObject::disconnect(obj, methodID, this, id);
                idToRpc.remove(id);
                idToParams.remove(id);
            }
            signalToId.remove(sig);
        }
    }

    int qt_metacall(QMetaObject::Call _c, int _id, void **_a)
    {
        // invoked when an attached signal is emitted
        if (QObject::qt_metacall(_c, _id, _a) < 0 || _c != QMetaObject::InvokeMetaMethod) return _id;
        QVariant v[8];
        const QList<int>& types = signalParameters.at(idToParams.value(_id));
        int n = types.count();
        int i;
        for (i = 0; i < n; i++)
        {
            v[i] = QVariant(types.at(i), _a[i+1]);
        }
        foreach(const QString& rpcName, idToRpc.values(_id))
        {
            rpc->call(rpcName, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
        }
        return -1;
    }
};

/**
 * \class QxtRPCService QxtRPCService
 * \ingroup QxtCore
 * \brief Transmits Qt signals over a QIODevice
 *
 * QxtRPCService is a tool that encapsulates Qt signals and transmits them over a QIODevice.
 * The signal is subsequently re-emitted on the receiving end of the connection.
 *
 * QxtRPCService can act as a client or a server. When acting as a server, it uses a
 * QxtAbstractConnectionManager to accept connections. When acting as a client, the application
 * should provide an already-connected QIODevice to the setDevice() function.
 *
 * All data types used in attached signals and slots must be declared and registered with QMetaType using
 * Q_DECLARE_METATYPE and qRegisterMetaType. Additional requirements may be imposed by the
 * QxtAbstractSignalSerializer subclass in use; the default QxtDataStreamSignalSerializer requires
 * that they have stream operators registered with qRegisterMetaTypeStreamOperators.
 *
 * Due to a restriction of Qt's signals and slots mechanism, the number of parameters that can be passed
 * to call() and its related functions, as well as the number of parameters to any signal or slot attached
 * to QxtRPCService, is limited to 8.
 */

QxtRPCServicePrivate::QxtRPCServicePrivate() : QObject(NULL)
{
    manager = NULL;
    device = NULL;
    serializer = new QxtDataStreamSignalSerializer;
}

void QxtRPCServicePrivate::clientConnected(QIODevice* dev, quint64 id)
{
    QxtMetaObject::connect(dev, SIGNAL(readyRead()), QxtMetaObject::bind(this, SLOT(clientData(quint64)), Q_ARG(quint64, id)));
    emit qxt_p().clientConnected(id);
    buffers[id] = QByteArray();
    if (dev->bytesAvailable() > 0)
        clientData(id);
}

void QxtRPCServicePrivate::clientDisconnected(QIODevice* dev, quint64 id)
{
    QObject::disconnect(dev, 0, this, 0);
    QObject::disconnect(dev, 0, &qxt_p(), 0);
    buffers.remove(id);
    emit qxt_p().clientDisconnected(id);
}

void QxtRPCServicePrivate::clientData(quint64 id)
{
    QIODevice* dev = manager->client(id);
    QByteArray& buf = buffers[id]; // caching to avoid repeated hash lookups
    buf.append(dev->readAll());
    while (serializer->canDeserialize(buf))
    {
        QxtAbstractSignalSerializer::DeserializedData data = serializer->deserialize(buf);
        // check for blank command
        if (serializer->isNoOp(data))
            continue;
        // check for errors
        if (serializer->isProtocolError(data))
        {
            qWarning() << "QxtRPCService: Invalid data received; disconnecting";
            qxt_p().disconnectClient(id);
            return;
        }
        // pad arguments to 8
        while (data.second.count() < 8)
            data.second << QVariant();
        dispatchFromClient(id, data.first, data.second[0], data.second[1], data.second[2], data.second[3], data.second[4], data.second[5], data.second[6], data.second[7]);
    }
}

void QxtRPCServicePrivate::serverData()
{
    serverBuffer.append(device->readAll());
    while (serializer->canDeserialize(serverBuffer))
    {
        QxtAbstractSignalSerializer::DeserializedData data = serializer->deserialize(serverBuffer);
        // check for blank command
        if (serializer->isNoOp(data))
            continue;
        // check for errors
        if (serializer->isProtocolError(data))
        {
            qWarning() << "QxtRPCService: Invalid data received; disconnecting";
            qxt_p().disconnectServer();
            return;
        }
        // pad arguments to 8
        while (data.second.count() < 8)
            data.second << QVariant();
        dispatchFromServer(data.first, data.second[0], data.second[1], data.second[2], data.second[3], data.second[4], data.second[5], data.second[6], data.second[7]);
    }
}

#define QXT_ARG(i) ((numParams>i)?QGenericArgument(p ## i .typeName(), p ## i.constData()):QGenericArgument())
void QxtRPCServicePrivate::dispatchFromServer(const QString& fn, const QVariant& p0, const QVariant& p1, const QVariant& p2, const QVariant& p3,
        const QVariant& p4, const QVariant& p5, const QVariant& p6, const QVariant& p7) const
{
    if (!connectedSlots.contains(fn)) return; // nothing connected
    foreach(const SlotDef& slot, connectedSlots.value(fn))
    {
        const QList<QByteArray>& params = slotParameters.value(qMakePair(slot.recv->metaObject(), slot.slot));
        int numParams = params.count();
        if (!QMetaObject::invokeMethod(slot.recv, slot.slot.constData(), slot.type, QXT_ARG(0), QXT_ARG(1), QXT_ARG(2),
                                       QXT_ARG(3), QXT_ARG(4), QXT_ARG(5), QXT_ARG(6), QXT_ARG(7)))
        {
            qWarning() << "QxtRPCService: invokeMethod for " << slot.recv << "::" << slot.slot << " failed";
        }
    }
}

void QxtRPCServicePrivate::dispatchFromClient(quint64 id, const QString& fn, const QVariant& p0, const QVariant& p1, const QVariant& p2, const QVariant& p3,
        const QVariant& p4, const QVariant& p5, const QVariant& p6, const QVariant& p7) const
{
    if (!connectedSlots.contains(fn)) return; // nothing connected
    foreach(const SlotDef& slot, connectedSlots.value(fn))
    {
        const QList<QByteArray>& params = slotParameters.value(qMakePair(slot.recv->metaObject(), slot.slot));
        int numParams = params.count();
        if (!QMetaObject::invokeMethod(slot.recv, slot.slot.constData(), slot.type, Q_ARG(quint64, id), QXT_ARG(0), QXT_ARG(1), QXT_ARG(2),
                                       QXT_ARG(3), QXT_ARG(4), QXT_ARG(5), QXT_ARG(6), QXT_ARG(7)))
        {
            qWarning() << "QxtRPCService: invokeMethod for " << slot.recv << "::" << slot.slot << " failed";
        }
    }
}

/**
 * Creates a QxtRPCService object with the given parent.
 */
QxtRPCService::QxtRPCService(QObject* parent) : QObject(parent)
{
    QXT_INIT_PRIVATE(QxtRPCService);
    qxt_d().introspector = new QxtRPCServiceIntrospector(this);
}

/**
 * Creates a QxtRPCService object with the given parent and connects it to the specified I/O device.
 *
 * The I/O device must already be opened for reading and writing.
 */
QxtRPCService::QxtRPCService(QIODevice* device, QObject* parent) : QObject(parent)
{
    QXT_INIT_PRIVATE(QxtRPCService);
    qxt_d().introspector = new QxtRPCServiceIntrospector(this);
    setDevice(device);
}

/**
 * Destroys the QxtRPCService object.
 */
QxtRPCService::~QxtRPCService()
{
    delete qxt_d().serializer;
}

/**
 * Returns true if the connection manager is accepting connections or if any clients
 * are currently connected. It is possible for both isServer() and isClient() to
 * return false if the connection manager is not accepting connections, no clients
 * are connected, and no QIODevice is set for a server.
 * \sa isClient
 */
bool QxtRPCService::isServer() const
{
    return qxt_d().manager && (qxt_d().manager->isAcceptingConnections() || qxt_d().manager->clientCount() > 0);
}

/**
 * Returns true if the QxtRPCService is currently communicating with a server. It
 * is possible for both isServer() and isClient() to return false if the connection
 * manager is not accepting connections, no clients are connected, and no QIODevice
 * is set for a server.
 * \sa isServer
 */
bool QxtRPCService::isClient() const
{
    return qxt_d().device != NULL;
}

/**
 * Disconnects a client using the attached connection manager.
 *
 * If connected to a server, this function is ignored with a warning.
 */
void QxtRPCService::disconnectClient(quint64 id)
{
    if (!isServer())
    {
        qWarning() << "QxtRPCService::disconnectClient: not operating as a server";
        return;
    }
    if (!qxt_d().manager->client(id))
    {
        qWarning() << "QxtRPCService::disconnectClient: no client with specified ID";
        return;
    }
    // QxtAbstractConnectionManager will emit disconnected(), which is chained to
    // QxtRPCService::clientDisconnected(), so the signal is not explicitly emitted here.
    qxt_d().manager->disconnect(id);
}

/**
 * Disconnects from the server. The QIODevice is deleted. Use takeDevice() to disconnect
 * from the server without deleting the device.
 *
 * If not connected to a server, for instance if acting as a server, this function is
 * ignored with a warning.
 * \sa device
 * \sa takeDevice
 */
void QxtRPCService::disconnectServer()
{
    if (!isClient())
    {
        qWarning() << "QxtRPCService::disconnectServer: not connected to a server";
        return;
    }
    delete takeDevice();
}

/**
 * Disconnects all clients, or disconnects from the server.
 */
void QxtRPCService::disconnectAll()
{
    if (isClient())
    {
        disconnectServer();
    }
    if (isServer())
    {
        QList<quint64> cList = clients();
        foreach(quint64 id, cList)
        {
            disconnectClient(id);
        }
    }
}

/**
 * Returns a list of client IDs for all connected clients.
 */
QList<quint64> QxtRPCService::clients() const
{
    if (!isServer())
    {
        qWarning() << "QxtRPCService::clients: not a server";
        return QList<quint64>();
    }
    return qxt_d().manager->clients();
}

/**
 * When operating as a client, returns the QIODevice connected to the server.
 * When operating as a server, or if not connected to a server, returns NULL.
 * \sa setDevice
 * \sa takeDevice
 */
QIODevice* QxtRPCService::device() const
{
    return qxt_d().device;
}

/**
 * Begins communicating with a server through the provided QIODevice.
 * If called while acting as a server, this function is ignored with a warning.
 * If called while another device is set, the original QIODevice is deleted.
 * The provided device will be reparented to the QxtRPCService.
 *
 * Note that because QIODevice is a generic interface, QxtRPCService does not
 * provide signals when this device is disconnected or has low-level errors.
 * Connect to the QIODevice subclass's signals directly if you need this
 * information.
 * \sa device
 */
void QxtRPCService::setDevice(QIODevice* dev)
{
    if (qxt_d().device)
        delete qxt_d().device;
    qxt_d().device = dev;
    dev->setParent(this);
    QObject::connect(dev, SIGNAL(readyRead()), &qxt_d(), SLOT(serverData()));
}

/**
 * When operating as a client, returns the QIODevice used to communicate with
 * the server. After this function is called, the QxtRPCService will no longer
 * be connected and device() will return NULL.
 * When operating as a server, or if not connected to a server, returns NULL.
 * \sa device
 */
QIODevice* QxtRPCService::takeDevice()
{
    QIODevice* rv = qxt_d().device;
    if (rv)
    {
        QObject::disconnect(rv, 0, this, 0);
        QObject::disconnect(rv, 0, &qxt_d(), 0);
        qxt_d().device = NULL;
    }
    return rv;
}

/**
 * Returns the signal serializer used to encode signals before transmission.
 * \sa setSerializer
 */
QxtAbstractSignalSerializer* QxtRPCService::serializer() const
{
    return qxt_d().serializer;
}

/**
 * Sets the signal serializer used to encode signals before transmission.
 * The existing serializer will be deleted.
 * \sa serializer
 */
void QxtRPCService::setSerializer(QxtAbstractSignalSerializer* serializer)
{
    delete qxt_d().serializer;
    qxt_d().serializer = serializer;
}

/**
 * Returns the connection manager used to accept incoming connections.
 * \sa setConnectionManager
 */
QxtAbstractConnectionManager* QxtRPCService::connectionManager() const
{
    return qxt_d().manager;
}

/**
 * Sets the connection manager used to accept incoming connections.
 * The existing manager will be deleted and the provided manager will
 * be reparented to the QxtRPCService.
 * \sa connectionManager
 */
void QxtRPCService::setConnectionManager(QxtAbstractConnectionManager* manager)
{
    if (qxt_d().manager)
        delete qxt_d().manager;
    qxt_d().manager = manager;
    manager->setParent(this);
    QObject::connect(manager, SIGNAL(newConnection(QIODevice*, quint64)), &qxt_d(), SLOT(clientConnected(QIODevice*, quint64)));
    QObject::connect(manager, SIGNAL(disconnected(QIODevice*, quint64)), &qxt_d(), SLOT(clientDisconnected(QIODevice*, quint64)));
}

/**
 * Attaches the given signal.
 *
 * When the attached signal is emitted, it will be transmitted to all connected servers, clients, or peers.
 * If an optional rpcFunction is provided, it will be used in place of the name of the transmitted signal.
 * Use the SIGNAL() macro to specify the signal, just as you would for QObject::connect().
 *
 * Like QObject::connect(), attachSignal returns false if the connection cannot be established.
 */
bool QxtRPCService::attachSignal(QObject* sender, const char* signal, const QString& rpcFunction)
{
    return qxt_d().introspector->addSignal(sender, signal, rpcFunction);
}

/**
 * Attaches the given slot.
 *
 * When a signal with the name given by rpcFunction is received from the network, the attached slot is executed.
 * Use the SLOT() macro to specify the slot, just as you would for QObject::connect().
 *
 * Like QObject::connect(), attachSignal returns false if the connection cannot be established.
 *
 * \Note When acting like a server, the first parameter of the slot must be <b>quint64 id</b>. The parameters of the incoming
 * signal follow. For example, SIGNAL(mySignal(QString)) from the client connects to SLOT(mySlot(quint64, QString)) on
 * the server.
 */
bool QxtRPCService::attachSlot(const QString& rpcFunction, QObject* recv, const char* slot, Qt::ConnectionType type)
{
    const QMetaObject* meta = recv->metaObject();
    QByteArray name = QxtMetaObject::methodName(slot);
    QPair<const QMetaObject*, QByteArray> info = qMakePair(meta, name);
    if (!qxt_d().slotParameters.count(info))
    {
        QByteArray norm = QxtMetaObject::methodSignature(slot);
        int methodID = meta->indexOfMethod(norm.constData());
        if (methodID < 0)
        {
            qWarning() << "QxtRPCService::attachSlot: " << recv << "::" << slot << " does not exist";
            return false;
        }
        QList<QByteArray> types = meta->method(methodID).parameterTypes();
        int ct = types.count();
        for (int i = 0; i < ct; i++)
        {
            int typeID = QMetaType::type(types.value(i).constData());
            if (typeID <= 0)
            {
                qWarning() << "QxtRPCService::attachSlot: cannot queue arguments of type " << types.value(i);
                return false;
            }
        }
        qxt_d().slotParameters[info] = types;
    }
    QxtRPCServicePrivate::SlotDef slotDef;
    slotDef.recv = recv;
    slotDef.slot = name;
    slotDef.type = type;
    QString rpcFunc = rpcFunction;
    if(QxtMetaObject::isSignalOrSlot(rpcFunction.toAscii().constData()))
        rpcFunc = QxtMetaObject::methodSignature(rpcFunction.toAscii().constData());
    qxt_d().connectedSlots[rpcFunc].append(slotDef);
    return true;
}

/**
 * Detaches all signals and slots for the given object.
 */
void QxtRPCService::detachObject(QObject* obj)
{
    detachSignals(obj);
    detachSlots(obj);
}

/**
 * Detaches all signals for the given object.
 */
void QxtRPCService::detachSignals(QObject* obj)
{
    qxt_d().introspector->disconnectObject(obj);
}

/**
 * Detaches all slots for the given object.
 */
void QxtRPCService::detachSlots(QObject* obj)
{
    foreach(const QString& name, qxt_d().connectedSlots.keys())
    {
        foreach(const QxtRPCServicePrivate::SlotDef& slot, qxt_d().connectedSlots.value(name))
        {
            if (slot.recv != obj) continue;
            qxt_d().connectedSlots[name].removeAll(slot);
        }
    }
}

/**
 * Sends the signal fn with the given parameter list to the server, or to all connected clients.
 *
 * The receiver is not obligated to act upon the signal. If no clients are connected, and if not
 * communicating with a server, this function does nothing.
 */
void QxtRPCService::call(QString fn, const QVariant& p1, const QVariant& p2, const QVariant& p3, const QVariant& p4,
                         const QVariant& p5, const QVariant& p6, const QVariant& p7, const QVariant& p8)
{
    if (isClient())
    {
        if(QxtMetaObject::isSignalOrSlot(fn.toAscii().constData()))
            fn = QxtMetaObject::methodSignature(fn.toAscii().constData());
        QByteArray data = qxt_d().serializer->serialize(fn, p1, p2, p3, p4, p5, p6, p7, p8);
        qxt_d().device->write(data);
    }

    if (isServer())
    {
        call(clients(), fn, p1, p2, p3, p4, p5, p6, p7, p8);
    }
}

/**
 * Sends the signal with the given parameter list to the provided list of clients.
 *
 * The receivers are not obligated to act upon the signal. If no client is connected with a provided ID, the ID
 * is ignored with a warning. If acting as a client, this function does nothing.
 */
void QxtRPCService::call(QList<quint64> ids, QString fn, const QVariant& p1, const QVariant& p2, const QVariant& p3, const QVariant& p4,
                         const QVariant& p5, const QVariant& p6, const QVariant& p7, const QVariant& p8)
{
    QByteArray data = qxt_d().serializer->serialize(fn, p1, p2, p3, p4, p5, p6, p7, p8);
    foreach(quint64 id, ids)
    {
        QIODevice* dev = qxt_d().manager->client(id);
        if (!dev)
        {
            qWarning() << "QxtRPCService::call: client ID not connected";
            continue;
        }
        dev->write(data);
    }
}

/**
 * Sends the signal fn with the given parameter list to the specified client.
 *
 * The receiver is not obligated to act upon the signal. If no client with the given ID is connected, the call
 * will be ignored with a warning. If acting as a client, this function does nothing.
 */
void QxtRPCService::call(quint64 id, QString fn, const QVariant& p1, const QVariant& p2, const QVariant& p3, const QVariant& p4,
                         const QVariant& p5, const QVariant& p6, const QVariant& p7, const QVariant& p8)
{
    call(QList<quint64>() << id, fn, p1, p2, p3, p4, p5, p6, p7, p8);
}

/**
 * Sends the signal fn with the given parameter list to all connected clients except for the client specified.
 *
 * The receiver is not obligated to act upon the signal. This function is useful for rebroadcasting a signal from one client
 * to all other connected clients. If acting as a client, this function does nothing.
 */
void QxtRPCService::callExcept(quint64 id, QString fn, const QVariant& p1, const QVariant& p2, const QVariant& p3, const QVariant& p4,
                               const QVariant& p5, const QVariant& p6, const QVariant& p7, const QVariant& p8)
{
    QList<quint64> ids = clients();
    ids.removeAll(id);
    call(ids, fn, p1, p2, p3, p4, p5, p6, p7, p8);
}

/**
 * Detaches all signals and slots for the object that emitted the signal connected to detachSender().
 */
void QxtRPCService::detachSender()
{
    detachObject(sender());
}

