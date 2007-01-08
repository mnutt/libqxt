#include "QxtRPCPeer.h"
#include <QMap>
#include <QDebug>
#include <QMetaMethod>
#include <QTcpSocket>
#include <QTcpServer>

class QxtIntrospector: public QObject {
    // This class MANUALLY implements the necessary parts of QObject.
    // Do NOT add the Q_OBJECT macro. As this class isn't intended
    // for direct use, it doesn't offer any sort of useful meta-object.
public:
    QxtIntrospector(QxtRPCPeer* parent, QObject* source, const char* signal);

    int qt_metacall(QMetaObject::Call _c, int _id, void **_a);

    QString rpcFunction;

private:
    QxtRPCPeer* peer;
    QList<int> argTypes;
};

struct QxtRPCConnection {
    QTcpSocket* socket;
    QByteArray buffer;
    QString lastMethod;
};

QxtRPCPeer::QxtRPCPeer(QObject* parent): QObject(parent) {
    m_rpctype = Peer;
    m_server = new QTcpServer(this);
    m_peer = new QTcpSocket(this);

    QObject::connect(m_peer, SIGNAL(connected()), this, SIGNAL(peerConnected()));
    QObject::connect(m_peer, SIGNAL(disconnected()), this, SIGNAL(peerDisconnected()));
    QObject::connect(m_peer, SIGNAL(disconnected()), this, SLOT(disconnectSender()));
    QObject::connect(m_peer, SIGNAL(readyRead()), this, SLOT(dataAvailable()));
    QObject::connect(m_peer, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(peerError(QAbstractSocket::SocketError)));
    QObject::connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void QxtRPCPeer::setRPCType(RPCTypes type) {
    if(m_peer->state()!= QAbstractSocket::UnconnectedState || m_server->isListening()) {
        qDebug() << "QxtRPCPeer: Cannot change RPC types while connected or listening";
        return;
    }
    m_rpctype = type;
}

QxtRPCPeer::RPCTypes QxtRPCPeer::rpcType() const {
    return m_rpctype;
}

void QxtRPCPeer::connect(QHostAddress addr, int port) {
    if(m_rpctype == Server) {
        qDebug() << "QxtRPCPeer: Cannot connect outward in Server mode";
        return;
    } else if(m_peer->state()!=QAbstractSocket::UnconnectedState) {
        qDebug() << "QxtRPCPeer: Already connected";
        return;
    }
    m_peer->connectToHost(addr, port);
}

bool QxtRPCPeer::listen(QHostAddress iface, int port) {
    if(m_rpctype == Client) {
        qDebug() << "QxtRPCPeer: Cannot listen in Client mode";
        return false;
    } else if(m_rpctype == Peer && m_peer->state()!=QAbstractSocket::UnconnectedState) {
        qDebug() << "QxtRPCPeer: Cannot listen while connected to a peer";
        return false;
    } else if(m_server->isListening()) {
        qDebug() << "QxtRPCPeer: Already listening";
        return false;
    }
    return m_server->listen(iface, port);
}

void QxtRPCPeer::disconnectPeer(int id) {
    if(m_rpctype == Server && id==0) {
        qDebug() << "QxtRPCPeer: Server mode does not have a peer";
        return;
    } else if(m_rpctype!= Server && id!=0) {
        qDebug() << "QxtRPCPeer: Must specify a client ID to disconnect";
        return;
    }
    QxtRPCConnection* conn;
    if(id==0) {
        m_peer->disconnectFromHost();
    } else if((conn = m_clients.take((QObject*)(id)))!= 0) {
        conn->socket->disconnectFromHost();
        conn->socket->deleteLater();
        delete conn;
    } else {
        qDebug() << "QxtRPCPeer: no client with id " << id;
    }
}

void QxtRPCPeer::disconnectAll() {
    if(m_rpctype!= Server)
        disconnectPeer();
    else {
        for(ConnHash::const_iterator i = m_clients.constBegin(); i!= m_clients.constEnd(); i++) {
            (*i)->socket->deleteLater();
            delete *i;
        }
        m_clients.clear();
    }
}

void QxtRPCPeer::stopListening() {
    if(!m_server->isListening()) {
        qDebug() << "QxtRPCPeer: Not listening";
        return;
    }
    m_server->close();
}

void QxtRPCPeer::attachSignal(QObject* sender, const char* signal, QString rpcFunction) {
    QByteArray sig(signal);
    if(rpcFunction=="") rpcFunction = sig.mid(1,sig.indexOf('(')-1);
    QxtIntrospector* spec = new QxtIntrospector(this, sender, signal);
    spec->rpcFunction = rpcFunction;
    attachedSignals.insertMulti(sender, spec);
}

void QxtRPCPeer::attachSlot(QString rpcFunction, QObject* recv, const char* slot) {
    attachedSlots[rpcFunction].append(QPair<QObject*, int>(recv, recv->metaObject()->indexOfMethod(recv->metaObject()->normalizedSignature(slot).mid(1))));
}

void QxtRPCPeer::detachSender() {
    detachObject(sender());
}

void QxtRPCPeer::detachObject(QObject* obj) {
    foreach(QxtIntrospector* i, attachedSignals.values(obj)) i->deleteLater();
    attachedSignals.remove(obj);
    foreach(QString slot, attachedSlots.keys()) {
        for(QList<QPair<QObject*, int> >::iterator i(attachedSlots[slot].begin());
                i!= attachedSlots[slot].end(); ) {
            if((*i).first == obj)
                i = attachedSlots[slot].erase(i);
            else
                i++;
        }
    }
}

QByteArray QxtRPCPeer::serialize(QString fn, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7, QVariant p8, QVariant p9) const {
    QByteArray rv;
    QDataStream str(&rv, QIODevice::WriteOnly);
    str << fn;
    unsigned char ct = 9;
    if(p1.isNull()) ct = 0;
    else if(p2.isNull()) ct = 1;
    else if(p3.isNull()) ct = 2;
    else if(p4.isNull()) ct = 3;
    else if(p5.isNull()) ct = 4;
    else if(p6.isNull()) ct = 5;
    else if(p7.isNull()) ct = 6;
    else if(p8.isNull()) ct = 7;
    else if(p9.isNull()) ct = 8;
    str << ct;
    if(ct--) str << p1;
    if(ct--) str << p2;
    if(ct--) str << p3;
    if(ct--) str << p4;
    if(ct--) str << p5;
    if(ct--) str << p6;
    if(ct--) str << p7;
    if(ct--) str << p8;
    if(ct--) str << p9;
    rv.replace(QByteArray("\\"), QByteArray("\\\\"));
    rv.replace(QByteArray("\n"), QByteArray("\\n"));
    rv.append("\n");
    return rv;
}

void QxtRPCPeer::call(QString fn, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7, QVariant p8, QVariant p9) {
    if(m_peer->state()!= QAbstractSocket::ConnectedState) return;
    m_peer->write(serialize(fn, p1, p2, p3, p4, p5, p6, p7, p8, p9));
}

void QxtRPCPeer::callClientList(QList<int> ids, QString fn, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7, QVariant p8) {
    QByteArray c = serialize(fn, p1, p2, p3, p4, p5, p6, p7, p8, QVariant());
    foreach(int id, ids) {
        QxtRPCConnection* conn = m_clients.value((QObject*)(id));
        if(!conn) {
            qDebug() << "QxtRPCPeer: no client with id" << id;
        } else {
            conn->socket->write(c);
        }
    }
}

void QxtRPCPeer::callClient(int id, QString fn, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7, QVariant p8) {
    callClientList(QList<int>() << id, fn, p1, p2, p3, p4, p5, p6, p7, p8);
}

void QxtRPCPeer::callClientsExcept(int id, QString fn, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7, QVariant p8) {
    QList<int> cs = clients();
    cs.removeAll(id);
    callClientList(cs, fn, p1, p2, p3, p4, p5, p6, p7, p8);
}

#define QXT_ARG(i) ((numParams>i)?QGenericArgument(p ## i .typeName(), p ## i .constData()):QGenericArgument())
void QxtRPCPeer::receivePeerSignal(QString fn, QVariant p0, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7, QVariant p8) const {
    QByteArray sig;
    int numParams;
    foreach(QxtRPCPeer::MethodID i, attachedSlots.value(fn)) {
        sig = i.first->metaObject()->method(i.second).signature();
        sig = sig.left(sig.indexOf('('));
        numParams = i.first->metaObject()->method(i.second).parameterTypes().count();
        QMetaObject::invokeMethod(i.first, sig, QXT_ARG(0), QXT_ARG(1), QXT_ARG(2), QXT_ARG(3), QXT_ARG(4), QXT_ARG(5), QXT_ARG(6), QXT_ARG(7), QXT_ARG(8));
    }
}

void QxtRPCPeer::receiveClientSignal(int id, QString fn, QVariant p0, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7) const {
    QByteArray sig;
    int numParams;
    foreach(QxtRPCPeer::MethodID i, attachedSlots.value(fn)) {
        sig = i.first->metaObject()->method(i.second).signature();
        sig = sig.left(sig.indexOf('('));
        numParams = i.first->metaObject()->method(i.second).parameterTypes().count();
        QMetaObject::invokeMethod(i.first, sig, Q_ARG(int, id), QXT_ARG(0), QXT_ARG(1), QXT_ARG(2), QXT_ARG(3), QXT_ARG(4), QXT_ARG(5), QXT_ARG(6), QXT_ARG(7));
    }
}
#undef QXT_ARG

void QxtRPCPeer::newConnection() {
    QTcpSocket* next = m_server->nextPendingConnection();
    if(m_rpctype == Peer) {
        if(m_peer->state()!= QAbstractSocket::UnconnectedState) {
            qDebug() << "QxtRPCPeer: Rejected connection from " << next->peerAddress().toString() << "; another peer is connected";
            next->disconnectFromHost();
            next->deleteLater();
        } else {
            m_peer->deleteLater();
            m_peer = next;
            QObject::connect(m_peer, SIGNAL(connected()), this, SIGNAL(peerConnected()));
            QObject::connect(m_peer, SIGNAL(disconnected()), this, SIGNAL(peerDisconnected()));
            QObject::connect(m_peer, SIGNAL(disconnected()), this, SLOT(disconnectSender()));
            QObject::connect(m_peer, SIGNAL(readyRead()), this, SLOT(dataAvailable()));
            QObject::connect(m_peer, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(peerError(QAbstractSocket::SocketError)));
            emit peerConnected();
        }
    } else {
        QxtRPCConnection* conn = new QxtRPCConnection;
        conn->socket = next;
        m_clients[next] = conn;
        QObject::connect(next, SIGNAL(disconnected()), this, SLOT(disconnectSender()));
        QObject::connect(next, SIGNAL(readyRead()), this, SLOT(dataAvailable()));
        QObject::connect(next, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(peerError(QAbstractSocket::SocketError)));
        emit clientConnected((int)(next));
    }
}

void QxtRPCPeer::dataAvailable() {
    if(m_rpctype!=Server && m_peer==sender()) {
        m_buffer.append(m_peer->readAll());
        processInput(m_peer, m_buffer);
        return;
    } else {
        QxtRPCConnection* conn = m_clients.value(sender());
        if(!conn) {
            qDebug() << "QxtRPCPeer: Unrecognized client object connected to dataAvailable";
            return;
        }
        conn->buffer.append(conn->socket->readAll());
        processInput(conn->socket, (conn->buffer));
        return;
    }
    qDebug() << "QxtRPCPeer: Unrecognized peer object connected to dataAvailable";
}

void QxtRPCPeer::disconnectSender() {
    QxtRPCConnection* conn = m_clients.value(sender());
    if(!conn) {
        if(m_peer!= qobject_cast<QTcpSocket*>(sender())) {
            qDebug() << "QxtRPCPeer: Unrecognized object connected to disconnectSender";
            return;
        }
        m_buffer.append(m_peer->readAll());
        m_buffer.append("\n");
        processInput(m_peer, m_buffer);
        m_buffer.clear();
        emit clientDisconnected((int)(sender()));
        return;
    }
    conn->buffer.append(conn->socket->readAll());
    conn->buffer.append("\n");
    processInput(conn->socket, conn->buffer);
    conn->socket->deleteLater();
    delete conn;
    m_clients.remove(sender());
}

void QxtRPCPeer::processInput(QTcpSocket* socket, QByteArray& buffer) {
    int pos;
    QByteArray cmd;
    while((pos = buffer.indexOf('\n'))!= -1) {
        cmd = buffer.left(pos-1);
        buffer = buffer.mid(pos+1);
        if(cmd.length()==0) continue;
        cmd.replace(QByteArray("\\n"), QByteArray("\n"));
        cmd.replace(QByteArray("\\\\"), QByteArray("\\"));
        QDataStream str(cmd);
        QString signal;
        unsigned char argCount;
        QVariant v[9];
        str >> signal >> argCount;
        for(int i=0; i<argCount; i++) str >> v[i];
        if(socket == m_peer) {
            receivePeerSignal(signal, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
        } else {
            receiveClientSignal((unsigned int)(socket), signal, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
        }
    }
}

QList<int> QxtRPCPeer::clients() const {
    QList<int> rv;
    QList<QObject*> cs = m_clients.keys();
    foreach(QObject* id, cs) rv << (const int)(id);
    return rv;
}

QxtIntrospector::QxtIntrospector(QxtRPCPeer* parent, QObject* source, const char* signal): QObject(parent) {
    peer = parent;
    int idx = source->metaObject()->indexOfSignal(QByteArray(signal).mid(1).constData());
    // Our "method" will have the first ID not used by the superclass.
    QMetaObject::connect(source, idx, this, QObject::staticMetaObject.methodCount());
    QObject::connect(source, SIGNAL(destroyed()), peer, SLOT(detachSender()));
    QList<QByteArray> p = source->metaObject()->method(idx).parameterTypes();
    int ct = p.count();
    for(int i=0; i<ct; i++) argTypes.append(QMetaType::type(p.value(i).constData()));
}

int QxtIntrospector::qt_metacall(QMetaObject::Call _c, int _id, void **_a) {
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if(_id==0) {
            QVariant v[9];
            int n = argTypes.size();
            for(int i=0; i<n; i++) v[i] = QVariant(argTypes[i], _a[i+1]);
            peer->call(rpcFunction, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
        }
        _id -= 1;
    }
    return _id;
}
