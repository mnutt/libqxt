/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Adam Higerd
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTRPCPEER
#define QXTRPCPEER

#include <QObject>
#include <QList>
#include <QVariant>
#include <QMultiHash>
#include <QPair>
#include <QString>
#include <QHostAddress>







class QxtIntrospector;
class QTcpServer;
class QTcpSocket;
struct QxtRPCConnection;
/**
\class QxtRPCPeer QxtRPCPeer

\ingroup network

\brief  transmitts Qt signals over a network connection

It can operate in peer-to-peer mode or client-server mode.
All data types used in attached signals and slots must be declared and registered with QMetaType using Q_DECLARE_METATYPE and qRegisterMetaType, and they must have stream operators registered with qRegisterMetaTypeStreamOperators.


*/

class QxtRPCPeer : public QObject {
Q_OBJECT
public:
	///Creates a QxRPCPeer object with the given parent.
    QxtRPCPeer(QObject* parent = 0);



    	/**
	This enum is used with the setRPCType() to describe the role played in a connection. It is also returned by rpcType(). 
	Constant    Value    Description 
	QxRPCPeer::Server    0x0    Listen for clients and accept multiple connections. 
	QxRPCPeer::Client    0x1    Connect to a server. 
	QxRPCPeer::Peer      0x2    Listen for a connection or connect to a peer. 
	*/
    enum RPCTypes { Server, Client, Peer };

	/**Sets the RPC type. 
	Attempting to change the RPC type while listening or connected will be ignored with a warning.*/
    void setRPCType(RPCTypes type);
	///Gets the current RPC type.
    RPCTypes rpcType() const;
	/**Connects to the specified peer or server on the selected port. 
	When the connection is complete, the peerConnected() signal will be emitted. 
	If an error occurs, the peerError() signal will be emitted.*/
    void connect(QHostAddress addr, int port = 80);
	/**Listens on the specified interface on the specified port for connections. 
	Attempting to listen while in Client mode or while connected in Peer mode will be ignored with a warning. 
	In Peer mode, only one connection can be active at a time. Additional incoming connections while connected to a peer will be dropped. When a peer connects, the peerConnected() signal will be emitted. 
	In Server mode, multiple connections can be active at a time. Each client that connects will be provided a unique ID, included in the clientConnected() signal that will be emitted.
	*/
    bool listen(QHostAddress iface = QHostAddress::Any, int port = 80);
	/**Disconnects from a server, client, or peer.
	Servers must provide a client ID, provided by the clientConnected() signal; clients and peers must not.
	*/
    void disconnectPeer(int id = -1);
	///Disconnects from all clients, or from the server or peer.
    void disconnectAll();
	/**Stops listening for connections. 
	Any connections still open will remain connected.
	*/
    void stopListening();
	

    QList<int> clients() const;


	/**Attaches the given signal. 
	When the attached signal is emitted, it will be transmitted to all connected servers, clients, or peers. If an optional rpcFunction is provided, it will be used as the name of the transmitted signal instead. 
	Use the SIGNAL() macro to specify the signal, just as you would for QObject::connect().
	*/
    void attachSignal(QObject* sender, const char* signal, QString rpcFunction = QString());
	/**
	Attaches the given slot. 
	When a signal with the name given by rpcFunction is received from the network, the attached slot is executed. 
	Use the SLOT() macro to specify the slot, just as you would for QObject::connect(). 
	\Note In Server mode, the first parameter of the slot must be int id. The parameters of the signal follow. For example, SIGNAL(mySignal(QString)) from the client connects to SLOT(mySlot(int, QString)) on the server.
	*/
    void attachSlot(QString rpcFunction, QObject* recv, const char* slot);
	///Detaches all signals and slots for the given object.
    void detachObject(QObject* obj);

public slots:
	/**Sends the signal fn with the given parameter list to the server or peer. 
	This function accepts up to 9 QVariant parameters. 
	The receiver is not obligated to act upon the signal. If no server or peer is connected, the call is ignored.*/
    void call(QString fn, QVariant p1 = QVariant(), QVariant p2 = QVariant(), QVariant p3 = QVariant(), QVariant p4 = QVariant(),
              QVariant p5 = QVariant(), QVariant p6 = QVariant(), QVariant p7 = QVariant(), QVariant p8 = QVariant(), QVariant p9 = QVariant());
    void callClientList(QList<int> ids, QString fn, QVariant p1 = QVariant(), QVariant p2 = QVariant(), QVariant p3 = QVariant(), QVariant p4 = QVariant(),
              QVariant p5 = QVariant(), QVariant p6 = QVariant(), QVariant p7 = QVariant(), QVariant p8 = QVariant());
	/**Sends the signal fn with the given parameter list to the selected client.
	This function accepts up to 8 QVariant parameters.  The receiver is not obligated to act upon the signal. If no client with the given ID is connected, the call will be ignored with a warning.*/
    void callClient(int id, QString fn, QVariant p1 = QVariant(), QVariant p2 = QVariant(), QVariant p3 = QVariant(), QVariant p4 = QVariant(),
              QVariant p5 = QVariant(), QVariant p6 = QVariant(), QVariant p7 = QVariant(), QVariant p8 = QVariant());
    void callClientsExcept(int id, QString fn, QVariant p1 = QVariant(), QVariant p2 = QVariant(), QVariant p3 = QVariant(), QVariant p4 = QVariant(),
              QVariant p5 = QVariant(), QVariant p6 = QVariant(), QVariant p7 = QVariant(), QVariant p8 = QVariant());
    	///Detaches all signals and slots for the object that emitted the signal connected to detachSender().
    void detachSender();

signals:
	///emitted after a successful connection to or from a peer or server.
    void peerConnected();
	/**This signal is emitted after a successful connection from a client. 
	The given ID is used for callClient() and disconnectPeer().
	*/
    void clientConnected(int id);
	///This signal is emitted when a peer or server is disconnected.
    void peerDisconnected();
	/**This signal is emitted when a client disconnects. The given ID is no longer valid.
	*/
    void clientDisconnected(int id);
	/**This signal is emitted whenever an error occurs on a socket.
	 Currently, no information about the socket that raised the error is available.*/
    void peerError(QAbstractSocket::SocketError);

protected:
    void receivePeerSignal(QString fn, QVariant p0 = QVariant(), QVariant p1 = QVariant(), QVariant p2 = QVariant(), QVariant p3 = QVariant(),
              QVariant p4 = QVariant(), QVariant p5 = QVariant(), QVariant p6 = QVariant(), QVariant p7 = QVariant(), QVariant p8 = QVariant()) const;
    void receiveClientSignal(int id, QString fn, QVariant p0 = QVariant(), QVariant p1 = QVariant(), QVariant p2 = QVariant(), QVariant p3 = QVariant(),
              QVariant p4 = QVariant(), QVariant p5 = QVariant(), QVariant p6 = QVariant(), QVariant p7 = QVariant()) const;
    QByteArray serialize(QString fn, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7, QVariant p8, QVariant p9) const;

private slots:
    void newConnection();
    void dataAvailable();
    void disconnectSender();

private:
    void processInput(QTcpSocket* socket, QByteArray& buffer);

    // Object -> introspector for each signal
    QMultiHash<QObject*, QxtIntrospector*> attachedSignals;
    // RPC function -> (object, slot ID)
    typedef QPair<QObject*, int> MethodID;
    QHash<QString, QList<MethodID> > attachedSlots;

    typedef QHash<QObject*, QxtRPCConnection*> ConnHash;
    QHash<QObject*, QxtRPCConnection*> m_clients;
    QTcpServer* m_server;
    QTcpSocket* m_peer;

    QByteArray m_buffer;
    RPCTypes m_rpctype;
};
#endif
